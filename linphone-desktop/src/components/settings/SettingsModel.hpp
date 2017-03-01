/*
 * SettingsModel.hpp
 * Copyright (C) 2017  Belledonne Communications, Grenoble, France
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Created on: February 2, 2017
 *      Author: Ronan Abhamon
 */

#ifndef SETTINGS_MODEL_H_
#define SETTINGS_MODEL_H_

#include <linphone++/linphone.hh>
#include <QObject>

// =============================================================================

class SettingsModel : public QObject {
  Q_OBJECT;

  // ===========================================================================
  // PROPERTIES.
  // ===========================================================================

  // Network. ------------------------------------------------------------------

  Q_PROPERTY(bool useSipInfoForDtmfs READ getUseSipInfoForDtmfs WRITE setUseSipInfoForDtmfs NOTIFY dtmfsProtocolChanged);
  Q_PROPERTY(bool useRfc2833ForDtmfs READ getUseRfc2833ForDtmfs WRITE setUseRfc2833ForDtmfs NOTIFY dtmfsProtocolChanged);

  Q_PROPERTY(bool ipv6Enabled READ getIpv6Enabled WRITE setIpv6Enabled NOTIFY ipv6EnabledChanged);

  Q_PROPERTY(int downloadBandwidth READ getDownloadBandwidth WRITE setDownloadBandwidth NOTIFY downloadBandWidthChanged);
  Q_PROPERTY(int uploadBandwidth READ getUploadBandwidth WRITE setUploadBandwidth NOTIFY uploadBandWidthChanged);

  Q_PROPERTY(
    bool adaptiveRateControlEnabled
    READ getAdaptiveRateControlEnabled
    WRITE setAdaptiveRateControlEnabled
    NOTIFY adaptiveRateControlEnabledChanged
  );

  // Q_PROPERTY(bool tcpPortEnabled READ getTcpPortEnabled WRITE setTcpPortEnabled NOTIFY tcpPortEnabledChanged);

  Q_PROPERTY(QList<int> audioPortRange READ getAudioPortRange WRITE setAudioPortRange NOTIFY audioPortRangeChanged);
  Q_PROPERTY(QList<int> videoPortRange READ getVideoPortRange WRITE setVideoPortRange NOTIFY videoPortRangeChanged);

  Q_PROPERTY(bool iceEnabled READ getIceEnabled WRITE setIceEnabled NOTIFY iceEnabledChanged);
  Q_PROPERTY(bool turnEnabled READ getTurnEnabled WRITE setTurnEnabled NOTIFY turnEnabledChanged);

  Q_PROPERTY(QString stunServer READ getStunServer WRITE setStunServer NOTIFY stunServerChanged);

  Q_PROPERTY(QString turnUser READ getTurnUser WRITE setTurnUser NOTIFY turnUserChanged);
  Q_PROPERTY(QString turnPassword READ getTurnPassword WRITE setTurnPassword NOTIFY turnPasswordChanged);

  Q_PROPERTY(int dscpSip READ getDscpSip WRITE setDscpSip NOTIFY dscpSipChanged);
  Q_PROPERTY(int dscpAudio READ getDscpAudio WRITE setDscpAudio NOTIFY dscpAudioChanged);
  Q_PROPERTY(int dscpVideo READ getDscpVideo WRITE setDscpVideo NOTIFY dscpVideoChanged);

  // Misc. ---------------------------------------------------------------------

  Q_PROPERTY(bool autoAnswerStatus READ getAutoAnswerStatus WRITE setAutoAnswerStatus NOTIFY autoAnswerStatusChanged);
  Q_PROPERTY(QString fileTransferUrl READ getFileTransferUrl WRITE setFileTransferUrl NOTIFY fileTransferUrlChanged);

  Q_PROPERTY(QString savedScreenshotsFolder READ getSavedScreenshotsFolder WRITE setSavedScreenshotsFolder NOTIFY savedScreenshotsFolderChanged);
  Q_PROPERTY(QString savedVideosFolder READ getSavedVideosFolder WRITE setSavedVideosFolder NOTIFY savedVideosFolderChanged);

public:
  SettingsModel (QObject *parent = Q_NULLPTR);

  // ===========================================================================
  // METHODS.
  // ===========================================================================

  // Network. ------------------------------------------------------------------

  bool getUseSipInfoForDtmfs () const;
  void setUseSipInfoForDtmfs (bool status);

  bool getUseRfc2833ForDtmfs () const;
  void setUseRfc2833ForDtmfs (bool status);

  bool getIpv6Enabled () const;
  void setIpv6Enabled (bool status);

  int getDownloadBandwidth () const;
  void setDownloadBandwidth (int bandwidth);

  int getUploadBandwidth () const;
  void setUploadBandwidth (int bandwidth);

  bool getAdaptiveRateControlEnabled () const;
  void setAdaptiveRateControlEnabled (bool status);

  // bool getTcpPortEnabled () const;
  // void setTcpPortEnabled (bool status);

  QList<int> getAudioPortRange () const;
  void setAudioPortRange (const QList<int> &range);

  QList<int> getVideoPortRange () const;
  void setVideoPortRange (const QList<int> &range);

  bool getIceEnabled () const;
  void setIceEnabled (bool status);

  bool getTurnEnabled () const;
  void setTurnEnabled (bool status);

  QString getStunServer () const;
  void setStunServer (const QString &stun_server);

  QString getTurnUser () const;
  void setTurnUser (const QString &user);

  QString getTurnPassword () const;
  void setTurnPassword (const QString &password);

  int getDscpSip () const;
  void setDscpSip (int dscp);

  int getDscpAudio () const;
  void setDscpAudio (int dscp);

  int getDscpVideo () const;
  void setDscpVideo (int dscp);

  // Misc. ---------------------------------------------------------------------

  bool getAutoAnswerStatus () const;
  void setAutoAnswerStatus (bool status);

  QString getFileTransferUrl () const;
  void setFileTransferUrl (const QString &url);

  QString getSavedScreenshotsFolder () const;
  void setSavedScreenshotsFolder (const QString &folder);

  QString getSavedVideosFolder () const;
  void setSavedVideosFolder (const QString &folder);

  // ---------------------------------------------------------------------------

  static const std::string UI_SECTION;

  // ===========================================================================
  // SIGNALS.
  // ===========================================================================

signals:
  // Network. ------------------------------------------------------------------

  void dtmfsProtocolChanged ();

  void ipv6EnabledChanged (bool status);

  void downloadBandWidthChanged (int bandwidth);
  void uploadBandWidthChanged (int bandwidth);

  bool adaptiveRateControlEnabledChanged (bool status);

  // void tcpPortEnabledChanged (bool status);

  void audioPortRangeChanged (int a, int b);
  void videoPortRangeChanged (int a, int b);

  void iceEnabledChanged (bool status);
  void turnEnabledChanged (bool status);

  void stunServerChanged (const QString &server);

  void turnUserChanged (const QString &user);
  void turnPasswordChanged (const QString &password);

  void dscpSipChanged (int dscp);
  void dscpAudioChanged (int dscp);
  void dscpVideoChanged (int dscp);

  // Misc. ---------------------------------------------------------------------

  void autoAnswerStatusChanged (bool status);
  void fileTransferUrlChanged (const QString &url);

  void savedScreenshotsFolderChanged (const QString &folder);
  void savedVideosFolderChanged (const QString &folder);

private:
  std::shared_ptr<linphone::Config> m_config;
};

#endif // SETTINGS_MODEL_H_