import QtQuick 2.9
import QtQuick.Window 2.3
import QtCharts 2.3
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4

import myTest 1.0

Window {
    id: root
    width: 500
    height: 500
    visible: true
    title:  qsTr("ChartView Example")

    Schedule {
        id: mySchedule
        onNameChanged:  { splineSeries.name  = mySchedule.getName()  }
        onColorChanged: { splineSeries.color = mySchedule.getColor() }
        onTypeChanged:()=>{
            splineSeries.clear()

            var vector_x = getX_vec()
            var vector_y = getY_vec()

            for(var i = 0; i < vector_x.length; i++) {
                splineSeries.append(vector_x[i], vector_y[i])
            }
            axisY.min = mySchedule.getY_min()
            axisY.max = mySchedule.getY_max()
        }
    }

    Item {
        anchors.fill: parent
        property variant othersSlice: 0

        ChartView {
            id: chartView
            title: "Leftclick to change schedule type, rightclick to change style"
            anchors.fill: parent
            antialiasing: true

            SplineSeries {
                id:splineSeries
                color:mySchedule.getColor()
                axisX: ValueAxis {
                    id:axisX
                    min: 0
                    max: mySchedule.getX_max()
                }
                axisY: ValueAxis {
                    id:axisY
                }
            }
        }

        MouseArea {
            id:mouseArea
            anchors.fill:parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if(mouse.button === Qt.LeftButton)
                {
                    if(mySchedule.getType()===ScheduleType.TYPE_NULL)
                        mySchedule.setType(ScheduleType.TYPE_X);

                    else if(mySchedule.getType()===ScheduleType.TYPE_X)
                        mySchedule.setType(ScheduleType.TYPE_SIN_X);

                    else if(mySchedule.getType()===ScheduleType.TYPE_SIN_X)
                        mySchedule.setType(ScheduleType.TYPE_POW_X);

                    else if(mySchedule.getType()===ScheduleType.TYPE_POW_X)
                        mySchedule.setType(ScheduleType.TYPE_LOG_X);

                    else if(mySchedule.getType()===ScheduleType.TYPE_LOG_X)
                        mySchedule.setType(ScheduleType.TYPE_MODULE_X);

                    else if(mySchedule.getType()===ScheduleType.TYPE_MODULE_X)
                        mySchedule.setType(ScheduleType.TYPE_X);
                }
                if(mouse.button === Qt.RightButton)
                {
                    if(mySchedule.getColor()==="purple") {
                        splineSeries.style = Qt.SolidLine
                        mySchedule.setColor("pink")
                    }

                    else if(mySchedule.getColor()==="pink") {
                        splineSeries.style= Qt.DashDotDotLine
                        mySchedule.setColor("blue")
                    }

                    else if(mySchedule.getColor()==="blue") {
                        splineSeries.style= Qt.DotLine
                        mySchedule.setColor("green")
                    }

                    else if(mySchedule.getColor()==="green") {
                       splineSeries.style= Qt.DashDotLine
                        mySchedule.setColor("red")
                    }

                    else if(mySchedule.getColor()==="red") {
                        splineSeries.style= Qt.DashLine
                        mySchedule.setColor("purple")
                    }
                }
            }
        }
    }
}
