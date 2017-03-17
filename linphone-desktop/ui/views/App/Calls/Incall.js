// =============================================================================
// `Incall.qml` Logic.
// =============================================================================

.import Linphone 1.0 as Linphone

.import 'qrc:/ui/scripts/Utils/utils.js' as Utils

// =============================================================================

function computeAvatarSize (maxSize) {
  var height = container.height
  var width = container.width

  var size = height < maxSize && height > 0 ? height : maxSize
  return size < width ? size : width
}

function handleVideoRequested () {
  var call = incall.call
  var dialog

  // Close dialog after 10s.
  var timeout = Utils.setTimeout(incall, 10000, function () {
    call.statusChanged.disconnect(endedHandler)
    dialog.close()
    call.rejectVideoRequest()
  })

  // Close dialog if call is ended.
  var endedHandler = function (status) {
    if (status === Linphone.CallModel.CallStatusEnded) {
      Utils.clearTimeout(timeout)
      call.statusChanged.disconnect(endedHandler)
      dialog.close()
    }
  }

  call.statusChanged.connect(endedHandler)

  // Ask video to user.
  dialog = Utils.openConfirmDialog(window, {
    descriptionText: qsTr('acceptVideoDescription'),
    exitHandler: function (status) {
      Utils.clearTimeout(timeout)
      call.statusChanged.disconnect(endedHandler)

      if (status) {
        call.acceptVideoRequest()
      } else {
        call.rejectVideoRequest()
      }
    },
    properties: {
      modality: Qt.NonModal
    },
    title: qsTr('acceptVideoTitle')
  })
}

function showFullScreen () {
  if (incall._fullscreen) {
    return
  }

  incall._fullscreen = Utils.openWindow('IncallFullscreenWindow', incall, {
    properties: {
      call: incall.call,
      callsWindow: incall
    }
  })
}

function updateCallQualityIcon () {
  var quality = call.quality
  callQuality.icon = 'call_quality_' + (
    // Note: `quality` is in the [0, 5] interval.
    // It's necessary to map in the `call_quality_` interval. ([0, 3])
    quality >= 0 ? Math.round(quality / (5 / 3)) : 0
  )
}