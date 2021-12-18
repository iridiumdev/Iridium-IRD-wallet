// Copyright (c) 2015-2017, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#include "DarkStyle.h"

namespace WalletGui {

DarkStyle::DarkStyle() : Style("dark", "Dark") {

}

QString DarkStyle::statusBarBackgroundColor() const {
  return "#1C1520";
}

QString DarkStyle::statusBarFontColor() const {
  return "#ffffff";
}

QString DarkStyle::headerBackgroundColor() const {
  return "#1C1520";
}

QString DarkStyle::headerBorderColor() const {
  return "#000000";
}

QString DarkStyle::addressFontColor() const {
  return "#ffffff";
}

QString DarkStyle::balanceFontColor() const {
  return "#ffffff";
}

QString DarkStyle::toolButtonBackgroundColorNormal() const {
  return "#1f1c33";
}

QString DarkStyle::toolButtonBackgroundColorHover() const {
  return "#4dec6d00";
}

QString DarkStyle::toolButtonBackgroundColorPressed() const {
  return "#514886";
}

QString DarkStyle::toolButtonFontColorNormal() const {
  return "#ffffff";
}

QString DarkStyle::toolButtonFontColorDisabled() const {
  return "#b2ffffff";
}

QString DarkStyle::toolBarBorderColor() const {
  return "#1C1520";
}

QString DarkStyle::getWalletSyncGifFile() const {
  return QString(":icons/dark/wallet-sync");
}

QPixmap DarkStyle::getLogoPixmap() const {
  return QPixmap(QString(":icons/dark/logo"));
}

QPixmap DarkStyle::getBalanceIcon() const {
  return QPixmap(QString(":icons/dark/balance"));
}

QPixmap DarkStyle::getConnectedIcon() const {
  return QPixmap(QString(":icons/dark/connected"));
}

QPixmap DarkStyle::getDisconnectedIcon() const {
  return QPixmap(QString(":icons/dark/disconnected"));
}

QPixmap DarkStyle::getEncryptedIcon() const {
  return QPixmap(QString(":icons/dark/encrypted"));
}

QPixmap DarkStyle::getNotEncryptedIcon() const {
  return QPixmap(QString(":icons/dark/decrypted"));
}

QPixmap DarkStyle::getSyncedIcon() const {
  return QPixmap(QString(":icons/dark/synced"));
}

}
