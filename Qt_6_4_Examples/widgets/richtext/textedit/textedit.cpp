// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "textedit.h"

#include <QActionGroup>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#include <QStringDecoder>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

#ifdef Q_OS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

TextEdit::TextEdit(QWidget *parent)
    : QMainWindow(parent)
{
#ifdef Q_OS_MACOS
    setUnifiedTitleAndToolBarOnMac(true);
#endif
    setWindowTitle(QCoreApplication::applicationName());

    textEdit = new QTextEdit(this);
    connect(textEdit, &QTextEdit::currentCharFormatChanged,
            this, &TextEdit::currentCharFormatChanged);
    connect(textEdit, &QTextEdit::cursorPositionChanged,
            this, &TextEdit::cursorPositionChanged);
    setCentralWidget(textEdit);

    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();

    {
        QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
        helpMenu->addAction(tr("About"), this, &TextEdit::about);
        helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    }

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    textEdit->setFont(textFont);
    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());

    auto *document = textEdit->document();
    connect(document, &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled);
    connect(document, &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(document, &QTextDocument::undoAvailable,
            actionUndo, &QAction::setEnabled);
    connect(document, &QTextDocument::redoAvailable,
            actionRedo, &QAction::setEnabled);

    setWindowModified(document->isModified());
    actionSave->setEnabled(document->isModified());
    actionUndo->setEnabled(document->isUndoAvailable());
    actionRedo->setEnabled(document->isRedoAvailable());

#ifndef QT_NO_CLIPBOARD
    actionCut->setEnabled(false);
    connect(textEdit, &QTextEdit::copyAvailable, actionCut, &QAction::setEnabled);
    actionCopy->setEnabled(false);
    connect(textEdit, &QTextEdit::copyAvailable, actionCopy, &QAction::setEnabled);

    connect(QGuiApplication::clipboard(), &QClipboard::dataChanged,
            this, &TextEdit::clipboardDataChanged);
#endif

    textEdit->setFocus();
    setCurrentFileName(QString());

#ifdef Q_OS_MACOS
    // Use dark text on light background on macOS, also in dark mode.
    QPalette pal = textEdit->palette();
    pal.setColor(QPalette::Base, QColor(Qt::white));
    pal.setColor(QPalette::Text, QColor(Qt::black));
    textEdit->setPalette(pal);
#endif
}

void TextEdit::closeEvent(QCloseEvent *e)
{
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}

void TextEdit::setupFileActions()
{
    QToolBar *tb = addToolBar(tr("File Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    QAction *a = menu->addAction(newIcon,  tr("&New"), this, &TextEdit::fileNew);
    tb->addAction(a);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png"));
    a = menu->addAction(openIcon, tr("&Open..."), this, &TextEdit::fileOpen);
    a->setShortcut(QKeySequence::Open);
    tb->addAction(a);

    menu->addSeparator();

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png"));
    actionSave = menu->addAction(saveIcon, tr("&Save"), this, &TextEdit::fileSave);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setEnabled(false);
    tb->addAction(actionSave);

    a = menu->addAction(tr("Save &As..."), this, &TextEdit::fileSaveAs);
    a->setPriority(QAction::LowPriority);
    menu->addSeparator();

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    const QIcon printIcon = QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png"));
    a = menu->addAction(printIcon, tr("&Print..."), this, &TextEdit::filePrint);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Print);
    tb->addAction(a);

    const QIcon filePrintIcon = QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png"));
    menu->addAction(filePrintIcon, tr("Print Preview..."), this, &TextEdit::filePrintPreview);

    const QIcon exportPdfIcon = QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png"));
    a = menu->addAction(exportPdfIcon, tr("&Export PDF..."), this, &TextEdit::filePrintPdf);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(Qt::CTRL | Qt::Key_D);
    tb->addAction(a);

    menu->addSeparator();
#endif

    a = menu->addAction(tr("&Quit"), this, &QWidget::close);
    a->setShortcut(Qt::CTRL | Qt::Key_Q);
}

void TextEdit::setupEditActions()
{
    QToolBar *tb = addToolBar(tr("Edit Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&Edit"));

    const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png"));
    actionUndo = menu->addAction(undoIcon, tr("&Undo"), textEdit, &QTextEdit::undo);
    actionUndo->setShortcut(QKeySequence::Undo);
    tb->addAction(actionUndo);

    const QIcon redoIcon = QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png"));
    actionRedo = menu->addAction(redoIcon, tr("&Redo"), textEdit, &QTextEdit::redo);
    actionRedo->setPriority(QAction::LowPriority);
    actionRedo->setShortcut(QKeySequence::Redo);
    tb->addAction(actionRedo);
    menu->addSeparator();

#ifndef QT_NO_CLIPBOARD
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png"));
    actionCut = menu->addAction(cutIcon, tr("Cu&t"), textEdit, &QTextEdit::cut);
    actionCut->setPriority(QAction::LowPriority);
    actionCut->setShortcut(QKeySequence::Cut);
    tb->addAction(actionCut);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png"));
    actionCopy = menu->addAction(copyIcon, tr("&Copy"), textEdit, &QTextEdit::copy);
    actionCopy->setPriority(QAction::LowPriority);
    actionCopy->setShortcut(QKeySequence::Copy);
    tb->addAction(actionCopy);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png"));
    actionPaste = menu->addAction(pasteIcon, tr("&Paste"), textEdit, &QTextEdit::paste);
    actionPaste->setPriority(QAction::LowPriority);
    actionPaste->setShortcut(QKeySequence::Paste);
    tb->addAction(actionPaste);
    if (const QMimeData *md = QGuiApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}

void TextEdit::setupTextActions()
{
    QToolBar *tb = addToolBar(tr("Format Actions"));
    QMenu *menu = menuBar()->addMenu(tr("F&ormat"));

    const QIcon boldIcon = QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png"));
    actionTextBold = menu->addAction(boldIcon, tr("&Bold"), this, &TextEdit::textBold);
    actionTextBold->setShortcut(Qt::CTRL | Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    tb->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    const QIcon italicIcon = QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png"));
    actionTextItalic = menu->addAction(italicIcon, tr("&Italic"), this, &TextEdit::textItalic);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL | Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    tb->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    const QIcon underlineIcon = QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png"));
    actionTextUnderline = menu->addAction(underlineIcon, tr("&Underline"), this, &TextEdit::textUnderline);
    actionTextUnderline->setShortcut(Qt::CTRL | Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    tb->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    menu->addSeparator();

    const QIcon leftIcon = QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png"));
    actionAlignLeft = new QAction(leftIcon, tr("&Left"), this);
    actionAlignLeft->setShortcut(Qt::CTRL | Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);
    const QIcon centerIcon = QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png"));
    actionAlignCenter = new QAction(centerIcon, tr("C&enter"), this);
    actionAlignCenter->setShortcut(Qt::CTRL | Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);
    const QIcon rightIcon = QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png"));
    actionAlignRight = new QAction(rightIcon, tr("&Right"), this);
    actionAlignRight->setShortcut(Qt::CTRL | Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);
    const QIcon fillIcon = QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png"));
    actionAlignJustify = new QAction(fillIcon, tr("&Justify"), this);
    actionAlignJustify->setShortcut(Qt::CTRL | Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);
    const QIcon indentMoreIcon = QIcon::fromTheme("format-indent-more", QIcon(rsrcPath + "/format-indent-more.png"));
    actionIndentMore = menu->addAction(indentMoreIcon, tr("&Indent"), this, &TextEdit::indent);
    actionIndentMore->setShortcut(Qt::CTRL | Qt::Key_BracketRight);
    actionIndentMore->setPriority(QAction::LowPriority);
    const QIcon indentLessIcon = QIcon::fromTheme("format-indent-less", QIcon(rsrcPath + "/format-indent-less.png"));
    actionIndentLess = menu->addAction(indentLessIcon, tr("&Unindent"), this, &TextEdit::unindent);
    actionIndentLess->setShortcut(Qt::CTRL | Qt::Key_BracketLeft);
    actionIndentLess->setPriority(QAction::LowPriority);

    // Make sure the alignLeft is always left of the alignRight
    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &TextEdit::textAlign);

    if (QGuiApplication::isLeftToRight()) {
        alignGroup->addAction(actionAlignLeft);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignRight);
    } else {
        alignGroup->addAction(actionAlignRight);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignLeft);
    }
    alignGroup->addAction(actionAlignJustify);

    tb->addActions(alignGroup->actions());
    menu->addActions(alignGroup->actions());
    tb->addAction(actionIndentMore);
    tb->addAction(actionIndentLess);
    menu->addAction(actionIndentMore);
    menu->addAction(actionIndentLess);

    menu->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = menu->addAction(pix, tr("&Color..."), this, &TextEdit::textColor);
    tb->addAction(actionTextColor);

    const QIcon underlineColorIcon(rsrcPath + "/textundercolor.png");
    actionUnderlineColor = menu->addAction(underlineColorIcon, tr("Underline color..."), this, &TextEdit::underlineColor);
    tb->addAction(actionUnderlineColor);

    menu->addSeparator();

    const QIcon checkboxIcon = QIcon::fromTheme("status-checkbox-checked", QIcon(rsrcPath + "/checkbox-checked.png"));
    actionToggleCheckState = menu->addAction(checkboxIcon, tr("Chec&ked"), this, &TextEdit::setChecked);
    actionToggleCheckState->setShortcut(Qt::CTRL | Qt::Key_K);
    actionToggleCheckState->setCheckable(true);
    actionToggleCheckState->setPriority(QAction::LowPriority);
    tb->addAction(actionToggleCheckState);

    tb = addToolBar(tr("Format Actions"));
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);

    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItems({"Standard",
                          "Bullet List (Disc)",
                          "Bullet List (Circle)",
                          "Bullet List (Square)",
                          "Task List (Unchecked)",
                          "Task List (Checked)",
                          "Ordered List (Decimal)",
                          "Ordered List (Alpha lower)",
                          "Ordered List (Alpha upper)",
                          "Ordered List (Roman lower)",
                          "Ordered List (Roman upper)",
                          "Heading 1",
                          "Heading 2",
                          "Heading 3",
                          "Heading 4",
                          "Heading 5",
                          "Heading 6"}),

    connect(comboStyle, &QComboBox::activated, this, &TextEdit::textStyle);

    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, &QComboBox::textActivated, this, &TextEdit::textFamily);

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, &QComboBox::textActivated, this, &TextEdit::textSize);
}

bool TextEdit::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QMimeDatabase db;
    const QString &mimeTypeName = db.mimeTypeForFileNameAndData(f, data).name();
    if (mimeTypeName == u"text/html") {
        auto encoding = QStringDecoder::encodingForHtml(data);
        QString str = QStringDecoder(encoding ? *encoding : QStringDecoder::Utf8)(data);
        QUrl fileUrl = f.startsWith(u':') ? QUrl(f) : QUrl::fromLocalFile(f);
        textEdit->document()->setBaseUrl(fileUrl.adjusted(QUrl::RemoveFilename));
        textEdit->setHtml(str);
#if QT_CONFIG(textmarkdownreader)
    } else if (mimeTypeName == u"text/markdown") {
        textEdit->setMarkdown(QString::fromUtf8(data));
#endif
    } else {
        textEdit->setPlainText(QString::fromUtf8(data));
    }

    setCurrentFileName(f);
    return true;
}

bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    setWindowModified(false);
}

void TextEdit::fileNew()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFileName({});
    }
}

void TextEdit::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters({
#if QT_CONFIG(texthtmlparser)
                                   "text/html",
#endif
#if QT_CONFIG(textmarkdownreader)

                                   "text/markdown",
#endif
                                   "text/plain"});
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().constFirst();
    if (load(fn))
        statusBar()->showMessage(tr("Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
}

bool TextEdit::fileSave()
{
    if (fileName.isEmpty() || fileName.startsWith(u":/"))
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    if (success) {
        textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar()->showMessage(tr("Could not write to file \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

bool TextEdit::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes{"text/plain",
#if QT_CONFIG(textodfwriter)
                          "application/vnd.oasis.opendocument.text",
#endif
#if QT_CONFIG(textmarkdownwriter)
                           "text/markdown",
#endif
                           "text/html"};
    fileDialog.setMimeTypeFilters(mimeTypes);
#if QT_CONFIG(textodfwriter)
    fileDialog.setDefaultSuffix("odt");
#endif
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().constFirst();
    setCurrentFileName(fn);
    return fileSave();
}

void TextEdit::filePrint()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dlg(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg.setOption(QAbstractPrintDialog::PrintSelection);
    dlg.setWindowTitle(tr("Print Document"));
    if (dlg.exec() == QDialog::Accepted)
        textEdit->print(&printer);
#endif
}

void TextEdit::filePrintPreview()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, textEdit, &QTextEdit::print);
    preview.exec();
#endif
}

void TextEdit::filePrintPdf()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
//! [0]
    QFileDialog fileDialog(this, tr("Export PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString pdfFileName = fileDialog.selectedFiles().constFirst();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfFileName);
    textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("Exported \"%1\"")
                             .arg(QDir::toNativeSeparators(pdfFileName)));
//! [0]
#endif
}

void TextEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamilies({f});
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (pointSize > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void TextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;
    QTextBlockFormat::MarkerType marker = QTextBlockFormat::MarkerType::NoMarker;

    switch (styleIndex) {
    case 1:
        style = QTextListFormat::ListDisc;
        break;
    case 2:
        style = QTextListFormat::ListCircle;
        break;
    case 3:
        style = QTextListFormat::ListSquare;
        break;
    case 4:
        if (cursor.currentList())
            style = cursor.currentList()->format().style();
        else
            style = QTextListFormat::ListDisc;
        marker = QTextBlockFormat::MarkerType::Unchecked;
        break;
    case 5:
        if (cursor.currentList())
            style = cursor.currentList()->format().style();
        else
            style = QTextListFormat::ListDisc;
        marker = QTextBlockFormat::MarkerType::Checked;
        break;
    case 6:
        style = QTextListFormat::ListDecimal;
        break;
    case 7:
        style = QTextListFormat::ListLowerAlpha;
        break;
    case 8:
        style = QTextListFormat::ListUpperAlpha;
        break;
    case 9:
        style = QTextListFormat::ListLowerRoman;
        break;
    case 10:
        style = QTextListFormat::ListUpperRoman;
        break;
    default:
        break;
    }

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    if (style == QTextListFormat::ListStyleUndefined) {
        blockFmt.setObjectIndex(-1);
        int headingLevel = styleIndex >= 11 ? styleIndex - 11 + 1 : 0; // H1 to H6, or Standard
        blockFmt.setHeadingLevel(headingLevel);
        cursor.setBlockFormat(blockFmt);

        int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
        QTextCharFormat fmt;
        fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
        fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.mergeCharFormat(fmt);
        textEdit->mergeCurrentCharFormat(fmt);
    } else {
        blockFmt.setMarker(marker);
        cursor.setBlockFormat(blockFmt);
        QTextListFormat listFmt;
        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }

    cursor.endEditBlock();
}

void TextEdit::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::underlineColor()
{
    QColor col = QColorDialog::getColor(Qt::black, this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setUnderlineColor(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::setChecked(bool checked)
{
    textStyle(checked ? 5 : 4);
}

void TextEdit::indent()
{
    modifyIndentation(1);
}

void TextEdit::unindent()
{
    modifyIndentation(-1);
}

void TextEdit::modifyIndentation(int amount)
{
    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    if (cursor.currentList()) {
        QTextListFormat listFmt = cursor.currentList()->format();
        // See whether the line above is the list we want to move this item into,
        // or whether we need a new list.
        QTextCursor above(cursor);
        above.movePosition(QTextCursor::Up);
        if (above.currentList() && listFmt.indent() + amount == above.currentList()->format().indent()) {
            above.currentList()->add(cursor.block());
        } else {
            listFmt.setIndent(listFmt.indent() + amount);
            cursor.createList(listFmt);
        }
    } else {
        QTextBlockFormat blockFmt = cursor.blockFormat();
        blockFmt.setIndent(blockFmt.indent() + amount);
        cursor.setBlockFormat(blockFmt);
    }
    cursor.endEditBlock();
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void TextEdit::cursorPositionChanged()
{
    alignmentChanged(textEdit->alignment());
    QTextList *list = textEdit->textCursor().currentList();
    if (list) {
        switch (list->format().style()) {
        case QTextListFormat::ListDisc:
            comboStyle->setCurrentIndex(1);
            break;
        case QTextListFormat::ListCircle:
            comboStyle->setCurrentIndex(2);
            break;
        case QTextListFormat::ListSquare:
            comboStyle->setCurrentIndex(3);
            break;
        case QTextListFormat::ListDecimal:
            comboStyle->setCurrentIndex(6);
            break;
        case QTextListFormat::ListLowerAlpha:
            comboStyle->setCurrentIndex(7);
            break;
        case QTextListFormat::ListUpperAlpha:
            comboStyle->setCurrentIndex(8);
            break;
        case QTextListFormat::ListLowerRoman:
            comboStyle->setCurrentIndex(9);
            break;
        case QTextListFormat::ListUpperRoman:
            comboStyle->setCurrentIndex(10);
            break;
        default:
            comboStyle->setCurrentIndex(-1);
            break;
        }
        switch (textEdit->textCursor().block().blockFormat().marker()) {
        case QTextBlockFormat::MarkerType::NoMarker:
            actionToggleCheckState->setChecked(false);
            break;
        case QTextBlockFormat::MarkerType::Unchecked:
            comboStyle->setCurrentIndex(4);
            actionToggleCheckState->setChecked(false);
            break;
        case QTextBlockFormat::MarkerType::Checked:
            comboStyle->setCurrentIndex(5);
            actionToggleCheckState->setChecked(true);
            break;
        }
    } else {
        int headingLevel = textEdit->textCursor().blockFormat().headingLevel();
        comboStyle->setCurrentIndex(headingLevel ? headingLevel + 10 : 0);
    }
}

void TextEdit::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QGuiApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}

void TextEdit::about()
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
        "rich text editing facilities in action, providing an example "
        "document for you to experiment with."));
}

void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void TextEdit::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}

void TextEdit::alignmentChanged(Qt::Alignment a)
{
    if (a.testFlag(Qt::AlignLeft))
        actionAlignLeft->setChecked(true);
    else if (a.testFlag(Qt::AlignHCenter))
        actionAlignCenter->setChecked(true);
    else if (a.testFlag(Qt::AlignRight))
        actionAlignRight->setChecked(true);
    else if (a.testFlag(Qt::AlignJustify))
        actionAlignJustify->setChecked(true);
}

