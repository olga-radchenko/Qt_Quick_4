import QtQuick 2.9
import QtQuick.Window 2.3
import QtCharts 2.3
import myTest 1.0

Window {
    id: root
    width: 500
    height: 500
    visible: true
    title:  qsTr("SplineSeries Example")

    Schedule {
        id: mySchedule
        Component.onCompleted: {
            var vector_x = getX_vec()
            var vector_y = getY_vec()
            for(var i = 0; i < vector_x.length; i++) {
                splineSeries.append( vector_x[i],  vector_y[i])
            }
        }
    }

    Item {
        anchors.fill: parent
        property variant othersSlice: 0

        ChartView {
            title: "Line"
            anchors.fill: parent
            antialiasing: true

            SplineSeries {
                name: "SplineSeries"
                id:splineSeries

                axisX: ValueAxis {
                    min: 0
                    max: mySchedule.getX_max()
                }
                axisY: ValueAxis {
                    min: mySchedule.getY_min()
                    max: mySchedule.getY_max()
                }
            }
        }
    }
}
