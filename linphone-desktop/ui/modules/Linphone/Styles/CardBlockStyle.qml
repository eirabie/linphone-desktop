pragma Singleton
import QtQuick 2.7

import Common 1.0

// =============================================================================

QtObject {
  property int spacing: 30
  property int width: 200

  property QtObject content: QtObject {
    property int height: 40
  }

  property QtObject description: QtObject {
    property color color: Colors.w
    property int fontSize: 10
    property int height: 40
  }

  property QtObject icon: QtObject {
    property int bottomMargin: 20
    property int size: 148
  }

  property QtObject title: QtObject {
    property color color: Colors.j
    property int bottomMargin: 10
    property int fontSize: 10
    property int height: 20
  }
}