import QtQuick 2.7
import QtQuick.Layouts 1.3

import Common 1.0
import Linphone 1.0
import Linphone.Styles 1.0
import Utils 1.0

// =============================================================================

Notification {
  id: notification

  // ---------------------------------------------------------------------------

  Rectangle {
    color: NotificationNewVersionAvailableStyle.color
    height: NotificationNewVersionAvailableStyle.height
    width: NotificationNewVersionAvailableStyle.width

    Icon {
      anchors {
        left: parent.left
        top: parent.top
      }

      icon: 'update_sign'
      iconSize: NotificationNewVersionAvailableStyle.iconSize
    }

    Loader {
      active: notificationData.url.length > 0
      anchors {
        fill: parent

        leftMargin: NotificationNewVersionAvailableStyle.leftMargin
        rightMargin: NotificationNewVersionAvailableStyle.rightMargin
      }

      sourceComponent: Text {
        anchors.fill: parent

        color: NotificationNewVersionAvailableStyle.message.color
        font.pointSize: NotificationNewVersionAvailableStyle.message.pointSize
        text: notificationData.message
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap

        MouseArea {
          anchors.fill: parent
          cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
          hoverEnabled: true

          onClicked: notification._close(function () {
            Qt.openUrlExternally(notificationData.url)
          })
        }
      }
    }
  }
}
