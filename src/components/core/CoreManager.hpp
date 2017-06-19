/*
 * CoreManager.hpp
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

#ifndef CORE_MANAGER_H_
#define CORE_MANAGER_H_

#include <QFuture>
#include <QFutureWatcher>
#include <QMutex>

#include "../calls/CallsListModel.hpp"
#include "../contacts/ContactsListModel.hpp"
#include "../settings/AccountSettingsModel.hpp"
#include "../settings/SettingsModel.hpp"
#include "../sip-addresses/SipAddressesModel.hpp"

#include "CoreHandlers.hpp"

// =============================================================================

class QTimer;

class CoreManager : public QObject {
  Q_OBJECT;

  Q_PROPERTY(QString version READ getVersion CONSTANT);
  Q_PROPERTY(QString downloadUrl READ getDownloadUrl CONSTANT);

public:
  ~CoreManager () = default;

  std::shared_ptr<linphone::Core> getCore () {
    Q_ASSERT(mCore != nullptr);
    return mCore;
  }

  std::shared_ptr<CoreHandlers> getHandlers () {
    Q_ASSERT(mHandlers != nullptr);
    return mHandlers;
  }

  // ---------------------------------------------------------------------------
  // Video render lock.
  // ---------------------------------------------------------------------------

  void lockVideoRender () {
    mMutexVideoRender.lock();
  }

  void unlockVideoRender () {
    mMutexVideoRender.unlock();
  }

  // ---------------------------------------------------------------------------
  // Singleton models.
  // ---------------------------------------------------------------------------

  CallsListModel *getCallsListModel () const {
    Q_ASSERT(mCallsListModel != nullptr);
    return mCallsListModel;
  }

  ContactsListModel *getContactsListModel () const {
    Q_ASSERT(mContactsListModel != nullptr);
    return mContactsListModel;
  }

  SipAddressesModel *getSipAddressesModel () const {
    Q_ASSERT(mSipAddressesModel != nullptr);
    return mSipAddressesModel;
  }

  SettingsModel *getSettingsModel () const {
    Q_ASSERT(mSettingsModel != nullptr);
    return mSettingsModel;
  }

  AccountSettingsModel *getAccountSettingsModel () const {
    Q_ASSERT(mAccountSettingsModel != nullptr);
    return mAccountSettingsModel;
  }

  // ---------------------------------------------------------------------------
  // Initialization.
  // ---------------------------------------------------------------------------

  static void init (QObject *parent, const QString &configPath);
  static void uninit ();

  static CoreManager *getInstance () {
    Q_ASSERT(mInstance != nullptr);
    return mInstance;
  }

  // ---------------------------------------------------------------------------

  // Must be used in a qml scene.
  // Warning: The ownership of `VcardModel` is `QQmlEngine::JavaScriptOwnership` by default.
  Q_INVOKABLE VcardModel *createDetachedVcardModel ();

  Q_INVOKABLE void forceRefreshRegisters ();

signals:
  void coreCreated ();
  void coreStarted ();

private:
  CoreManager (QObject *parent, const QString &configPath);

  void setDatabasesPaths ();
  void setOtherPaths ();
  void setResourcesPaths ();

  void createLinphoneCore (const QString &configPath);

  QString getVersion () const;

  void iterate ();

  static QString getDownloadUrl ();

  std::shared_ptr<linphone::Core> mCore;
  std::shared_ptr<CoreHandlers> mHandlers;

  CallsListModel *mCallsListModel;
  ContactsListModel *mContactsListModel;
  SipAddressesModel *mSipAddressesModel;
  SettingsModel *mSettingsModel;
  AccountSettingsModel *mAccountSettingsModel;

  QTimer *mCbsTimer;

  QFuture<void> mPromiseBuild;
  QFutureWatcher<void> mPromiseWatcher;

  QMutex mMutexVideoRender;

  static CoreManager *mInstance;
};

#endif // CORE_MANAGER_H_
