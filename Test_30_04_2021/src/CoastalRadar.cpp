#include "CoastalRadar.h"
#include "CoastalRadarMessage.h"
#include "Radar.h"

CoastalRadar::~CoastalRadar() { }

void CoastalRadar::internal_thread_iteration()
{
}

/*
реализовать следующую логику: каждые 100 мс радар посылает приемнику
сообщение с координатами, размером объекта, вектором скорости и отметкой
времени. Обратить внимание на потокобезопасность при передаче сообщения.
Объект, данные которого передаются радаром, должен совершать эволюции в
пространстве — перемещаться по какой-нибудь траектории в пределах куба
размерами 100 х 100 х 100 м.
*/