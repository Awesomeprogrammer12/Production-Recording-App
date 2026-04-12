import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    anchors.fill: parent
    property string mode  :"Daily" //Weekly,Monthly,Yearly
    property string bg    :"#1f1f1f"
    property string fg    :"#FDFDFD"
    property var btnColors: ["#3f3f3f", "#5f5f5f"]
    property string accent: "purple"
    color:bg // light gray background for now
    //the sidebar consists of a drawer and daily weakly monthly yeary toggle buttons
    Rectangle{
        id:sideBar
        height:parent.height
        width:parent.width*0.1
        color:btnColors[0]
        anchors{
            left:parent.left
        }
        Behavior on width{
            NumberAnimation{
                duration:500
                easing.type: Easing.OutBounce
            }
        }

        Button{
            id:sideBarDrawer
            width:sideBar.width*0.8 //thats 80 %
            height:40
            anchors{
                top:parent.top
                horizontalCenter: parent.horizontalCenter
            }
            icon.source:"qrc:/img/menu.png"
            icon.color:fg
            icon.width:32
            icon.height:32
            Rectangle{
                id:sideBarDrawerBackground
                color:sideBar.color
                anchors.fill: parent
            }Rectangle{
                id:sideBarDrawerBack
                radius:20
                anchors.fill: parent
                color:sideBarDrawerMouseArea.pressed?bg:(sideBarDrawerMouseArea.containsMouse?btnColors[1]:btnColors[0])
            }

            MouseArea{
                id:sideBarDrawerMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked:{
                    sideBarButtons.visible = sideBarButtons.visible===true?false:true
                    if(sideBar.width > root.width *0.09){
                        sideBar.width = root.width *0.03
                    }else if(sideBar.width < root.width *0.09){
                        sideBar.width = root.width *0.1
                    }
                }
            }
        }

        Column{
            id:sideBarButtons
            visible:true
            anchors{
                top:sideBarDrawer.bottom
                topMargin: 5
                bottom:parent.bottom
                left:parent.left
                leftMargin: sideBarButtonsIndicator.width
                right:parent.right
            }
            Button{
                id:daily
                text:"Daily"
                width:sideBar.width*0.9
                palette.buttonText: fg
                height:40
                Rectangle{
                    anchors.fill: parent
                    color:sideBar.color
                }
                Rectangle{
                    anchors.fill: parent
                    radius:10
                    color:dailyMouseArea.pressed?bg:(dailyMouseArea.containsMouse?btnColors[1]:btnColors[0])
                }
                MouseArea{
                    id:dailyMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:{
                        mode = "Daily"
                    }
                }
            }
            Button{
                id:weekly
                text:"Weekly"
                width:sideBar.width*0.9
                palette.buttonText: fg
                height:40
                Rectangle{
                    anchors.fill: parent
                    color:sideBar.color
                }
                Rectangle{
                    anchors.fill: parent
                    radius:10
                    color:weeklyMouseArea.pressed?bg:(weeklyMouseArea.containsMouse?btnColors[1]:btnColors[0])
                }
                MouseArea{
                    id:weeklyMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:{
                        mode = "Weekly"
                    }
                }
            }
            Button{
                id:monthly
                text:"Monthly"
                width:sideBar.width*0.9
                palette.buttonText: fg
                height:40
                Rectangle{
                    anchors.fill: parent
                    color:sideBar.color
                }
                Rectangle{
                    anchors.fill: parent
                    radius:10
                    color:monthlyMouseArea.pressed?bg:(monthlyMouseArea.containsMouse?btnColors[1]:btnColors[0])
                }
                MouseArea{
                    id:monthlyMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:{
                        mode = "Monthly"
                    }
                }
            }
            Button{
                id:yearly
                text:"Yearly"
                width:sideBar.width*0.9
                palette.buttonText: fg
                height:40
                Rectangle{
                    anchors.fill: parent
                    color:sideBar.color
                }
                Rectangle{
                    anchors.fill: parent
                    radius:10
                    color:yearlyMouseArea.pressed?bg:(yearlyMouseArea.containsMouse?btnColors[1]:btnColors[0])
                }
                MouseArea{
                    id:yearlyMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:{
                        mode = "Yearly"
                    }
                }
            }

        }
        Rectangle{
            id:sideBarButtonsIndicator
            color:accent
            width: parent.width *0.05
            height:daily.height
            x:0.5
            radius: width*0.3
            y: {
               let target;
               if (mode === "Daily") target = daily;
               else if (mode === "Weekly") target = weekly;
               else if (mode === "Monthly") target = monthly;
               else if (mode === "Yearly") target = yearly;

               if (target) {
                   sideBarButtonsIndicator.height = target.height
                   return target.y+target.height+5;
               }
               return daily.y;
            }
            Behavior on y{
                NumberAnimation{
                    duration:250
                    easing.type: Easing.OutBounce
                }
            }
        }

        Rectangle{
            id:sideBarBorder
            height:parent.height
            color:fg
            width:1
            anchors{
                right:parent.right
            }
        }

    }
    Rectangle{
        id:mainUI
        anchors{
            right:parent.right
            left:sideBar.right
            top:parent.top
            bottom:parent.bottom
        }
    }
}
