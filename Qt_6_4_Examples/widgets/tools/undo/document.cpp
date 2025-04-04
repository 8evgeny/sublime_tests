// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "document.h"
#include "commands.h"

#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>
#include <QUndoStack>

static constexpr int resizeHandleWidth = 6;

/******************************************************************************
** Shape
*/

const QSize Shape::minSize(80, 50);

Shape::Shape(Type type, const QColor &color, const QRect &rect)
    : m_type(type), m_rect(rect), m_color(color)
{
}

Shape::Type Shape::type() const
{
    return m_type;
}

QRect Shape::rect() const
{
    return m_rect;
}

QColor Shape::color() const
{
    return m_color;
}

QString Shape::name() const
{
    return m_name;
}

QRect Shape::resizeHandle() const
{
    QPoint br = m_rect.bottomRight();
    return QRect(br - QPoint(resizeHandleWidth, resizeHandleWidth), br);
}

QString Shape::typeToString(Type type)
{
    switch (type) {
        case Rectangle:
            return QLatin1String("Rectangle");
        case Circle:
            return QLatin1String("Circle");
        case Triangle:
            return QLatin1String("Triangle");
    }

    return QString();
}

Shape::Type Shape::stringToType(const QString &s, bool *ok)
{
    if (ok != nullptr)
        *ok = true;

    if (s == QLatin1String("Rectangle"))
        return Rectangle;
    if (s == QLatin1String("Circle"))
        return Circle;
    if (s == QLatin1String("Triangle"))
        return Triangle;

    if (ok != nullptr)
        *ok = false;
    return Rectangle;
}

/******************************************************************************
** Document
*/

Document::Document(QWidget *parent)
    : QWidget(parent), m_undoStack(new QUndoStack(this))
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);

    QPalette pal = palette();
    pal.setBrush(QPalette::Base, QPixmap(":/icons/background.png"));
    pal.setColor(QPalette::HighlightedText, Qt::red);
    setPalette(pal);
}

QString Document::addShape(const Shape &shape)
{
    QString name = Shape::typeToString(shape.type());
    name = uniqueName(name);

    m_shapeList.append(shape);
    m_shapeList[m_shapeList.count() - 1].m_name = name;
    setCurrentShape(m_shapeList.count() - 1);

    return name;
}

void Document::deleteShape(const QString &shapeName)
{
    int index = indexOf(shapeName);
    if (index == -1)
        return;

    update(m_shapeList.at(index).rect());

    m_shapeList.removeAt(index);

    if (index <= m_currentIndex) {
        m_currentIndex = -1;
        if (index == m_shapeList.count())
            --index;
        setCurrentShape(index);
    }
}

Shape Document::shape(const QString &shapeName) const
{
    int index = indexOf(shapeName);
    if (index == -1)
        return Shape();
    return m_shapeList.at(index);
}

void Document::setShapeRect(const QString &shapeName, const QRect &rect)
{
    int index = indexOf(shapeName);
    if (index == -1)
        return;

    Shape &shape = m_shapeList[index];

    update(shape.rect());
    update(rect);

    shape.m_rect = rect;
}

void Document::setShapeColor(const QString &shapeName, const QColor &color)
{

    int index = indexOf(shapeName);
    if (index == -1)
        return;

    Shape &shape = m_shapeList[index];
    shape.m_color = color;

    update(shape.rect());
}

QUndoStack *Document::undoStack() const
{
    return m_undoStack;
}

bool Document::load(QTextStream &stream)
{
    m_shapeList.clear();

    while (!stream.atEnd()) {
        QString shapeType, shapeName, colorName;
        int left, top, width, height;
        stream >> shapeType >> shapeName >> colorName >> left >> top >> width >> height;
        if (stream.status() != QTextStream::Ok)
            return false;
        bool ok;
        Shape::Type type = Shape::stringToType(shapeType, &ok);
        if (!ok)
            return false;
        QColor color(colorName);
        if (!color.isValid())
            return false;

        Shape shape(type);
        shape.m_name = shapeName;
        shape.m_color = color;
        shape.m_rect = QRect(left, top, width, height);

        m_shapeList.append(shape);
    }

    m_currentIndex = m_shapeList.isEmpty() ? -1 : 0;

    return true;
}

void Document::save(QTextStream &stream)
{
    for (int i = 0; i < m_shapeList.count(); ++i) {
        const Shape &shape = m_shapeList.at(i);
        QRect r = shape.rect();
        stream << Shape::typeToString(shape.type()) << QLatin1Char(' ')
                << shape.name() << QLatin1Char(' ')
                << shape.color().name() << QLatin1Char(' ')
                << r.left() << QLatin1Char(' ')
                << r.top() << QLatin1Char(' ')
                << r.width() << QLatin1Char(' ')
                << r.height();
        if (i != m_shapeList.count() - 1)
            stream << QLatin1Char('\n');
    }
    m_undoStack->setClean();
}

QString Document::fileName() const
{
    return m_fileName;
}

void Document::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

int Document::indexAt(const QPoint &pos) const
{
    for (int i = m_shapeList.count() - 1; i >= 0; --i) {
        if (m_shapeList.at(i).rect().contains(pos))
            return i;
    }
    return -1;
}

void Document::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    int index = indexAt(event->position().toPoint());;
    if (index != -1) {
        setCurrentShape(index);

        const Shape &shape = m_shapeList.at(index);
        m_resizeHandlePressed = shape.resizeHandle().contains(event->position().toPoint());

        if (m_resizeHandlePressed)
            m_mousePressOffset = shape.rect().bottomRight() - event->position().toPoint();
        else
            m_mousePressOffset = event->position().toPoint() - shape.rect().topLeft();
    }
    m_mousePressIndex = index;
}

void Document::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    m_mousePressIndex = -1;
}

void Document::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    if (m_mousePressIndex == -1)
        return;

    const Shape &shape = m_shapeList.at(m_mousePressIndex);

    QRect rect;
    if (m_resizeHandlePressed) {
        rect = QRect(shape.rect().topLeft(), event->position().toPoint() + m_mousePressOffset);
    } else {
        rect = shape.rect();
        rect.moveTopLeft(event->position().toPoint() - m_mousePressOffset);
    }

    QSize size = rect.size().expandedTo(Shape::minSize);
    rect.setSize(size);

    m_undoStack->push(new SetShapeRectCommand(this, shape.name(), rect));
}

static QGradient gradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
    result.setColorAt(0, c.darker(150));
    result.setColorAt(0.5, c.lighter(200));
    result.setColorAt(1, c.darker(150));
    return result;
}

static QPolygon triangle(const QRect &rect)
{
    QPolygon result(3);
    result.setPoint(0, rect.center().x(), rect.top());
    result.setPoint(1, rect.right(), rect.bottom());
    result.setPoint(2, rect.left(), rect.bottom());
    return result;
}

void Document::paintEvent(QPaintEvent *event)
{
    QRegion paintRegion = event->region();
    QPainter painter(this);
    QPalette pal = palette();

    for (int i = 0; i < m_shapeList.count(); ++i) {
        const Shape &shape = m_shapeList.at(i);

        if (!paintRegion.contains(shape.rect()))
            continue;

        QPen pen = pal.text().color();
        pen.setWidth(i == m_currentIndex ? 2 : 1);
        painter.setPen(pen);
        painter.setBrush(gradient(shape.color(), shape.rect()));

        QRect rect = shape.rect();
        rect.adjust(1, 1, -resizeHandleWidth/2, -resizeHandleWidth/2);

        // paint the shape
        switch (shape.type()) {
            case Shape::Rectangle:
                painter.drawRect(rect);
                break;
            case Shape::Circle:
                painter.setRenderHint(QPainter::Antialiasing);
                painter.drawEllipse(rect);
                painter.setRenderHint(QPainter::Antialiasing, false);
                break;
            case Shape::Triangle:
                painter.setRenderHint(QPainter::Antialiasing);
                painter.drawPolygon(triangle(rect));
                painter.setRenderHint(QPainter::Antialiasing, false);
                break;
        }

        // paint the resize handle
        painter.setPen(pal.text().color());
        painter.setBrush(Qt::white);
        painter.drawRect(shape.resizeHandle().adjusted(0, 0, -1, -1));

        // paint the shape name
        painter.setBrush(pal.text());
        if (shape.type() == Shape::Triangle)
            rect.adjust(0, rect.height()/2, 0, 0);
        painter.drawText(rect, Qt::AlignCenter, shape.name());
    }
}

void Document::setCurrentShape(int index)
{
    QString currentName;

    if (m_currentIndex != -1)
        update(m_shapeList.at(m_currentIndex).rect());

    m_currentIndex = index;

    if (m_currentIndex != -1) {
        const Shape &current = m_shapeList.at(m_currentIndex);
        update(current.rect());
        currentName = current.name();
    }

    emit currentShapeChanged(currentName);
}

int Document::indexOf(const QString &shapeName) const
{
    for (int i = 0; i < m_shapeList.count(); ++i) {
        if (m_shapeList.at(i).name() == shapeName)
            return i;
    }
    return -1;
}

QString Document::uniqueName(const QString &name) const
{
    QString unique;

    for (int i = 0; ; ++i) {
        unique = name;
        if (i > 0)
            unique += QString::number(i);
        if (indexOf(unique) == -1)
            break;
    }

    return unique;
}

QString Document::currentShapeName() const
{
    if (m_currentIndex == -1)
        return QString();
    return m_shapeList.at(m_currentIndex).name();
}

