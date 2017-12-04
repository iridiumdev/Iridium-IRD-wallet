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

#include <QIcon>

#include "Style.h"

namespace WalletGui {

Style::Style(const QString& _styleId, const QString& _styleName) : m_styleId(_styleId), m_styleName(_styleName) {
}

Style::~Style() {
}

QString Style::getStyleId() const {
  return m_styleId;
}

QString Style::getStyleName() const {
  return m_styleName;
}

QString Style::fontFamily() const {
  return "Open Sans";
}

int Style::viewItemHeight() const {
  return 46;
}

QString Style::fontColorGray() const {
  return "#888888";
}

QString Style::fontColorGreen() const {
  return "#482251";
}

QString Style::fontColorRed() const {
  return "#ef3131";
}

QString Style::fontColorBlueNormal() const {
  return "#21414D";
}

QString Style::fontColorBlueHover() const {
  return "#00090C";
}

QString Style::fontColorBluePressed() const {
  return "#deec6d00";
}

QString Style::backgroundColorGray() const {
  return "#f4f4f4";
}

QString Style::backgroundButtonColorGrayHover() const {
  return "#fbfbfb";
}

QString Style::backgroundColorBlueNormal() const {
  return "#73517B";
}

QString Style::backgroundColorBlueHover() const {
  return "#AE9DB2";
}

QString Style::backgroundColorBluePressed() const {
  return "#482251";
}

QString Style::backgroundColorBlueDisabled() const {
  return "#7f73517B";
}

QString Style::backgroundColorGrayNormal() const {
  return "#9e9e9e";
}

QString Style::backgroundColorGrayHover() const {
  return "#a8a8a8";
}

QString Style::backgroundColorGrayPressed() const {
  return "#bfbebe";
}

QString Style::backgroundColorGreen() const {
  return fontColorGreen();
}

QString Style::backgroundColorGreenHover() const {
  return "#727931";
}

QString Style::backgroundColorAlternate() const {
  return "#80FFF8E8";
}

QString Style::borderColor() const {
  return "#dddddd";
}

QString Style::borderColorDark() const {
  return "#bbbbbb";
}

QString Style::selectionColor() const {
  return "#5f9cc7";
}

QString Style::glassColor() const {
  return "#eaffffff";
}

QIcon Style::getSystemTrayIcon() const {
#ifdef Q_OS_MAC
  return QIcon(":images/iridium_mac");
#elif defined(Q_OS_LINUX)
  return QIcon(":images/iridium_lin");
#elif defined(Q_OS_WIN)
  return QIcon(":images/iridium_win");
#endif
}

QString Style::makeStyleSheet(const QString& _styleSheetTemplate) const {
  QString styleSheet(_styleSheetTemplate);
  return styleSheet.
    replace("%fontFamily%", fontFamily()).
    replace("%currentTheme%", getStyleId()).
    replace("%viewItemHeight%", QString("%1px").arg(viewItemHeight())).
    replace("%fontSizeTiny%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_TINY))).
    replace("%fontSizeSmall%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_SMALL))).
    replace("%fontSizeNormal%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_NORMAL))).
    replace("%fontSizeExtraNormal%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_EXTRA_NORMAL))).
    replace("%fontSizeLarge%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_LARGE))).
    replace("%fontSizeExtraLarge%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_EXTRA_LARGE))).
    replace("%fontSizeHuge%", QString("%1px").arg(static_cast<quint8>(FontSize::FONT_HUGE))).
    replace("%fontColorGray%", fontColorGray()).
    replace("%fontColorGreen%", fontColorGreen()).
    replace("%fontColorRed%", fontColorRed()).
    replace("%fontColorBlueNormal%", fontColorBlueNormal()).
    replace("%fontColorBlueHover%", fontColorBlueHover()).
    replace("%fontColorBluePressed%", fontColorBluePressed()).
    replace("%backgroundColorGray%", backgroundColorGray()).
    replace("%backgroundButtonColorGrayHover%", backgroundButtonColorGrayHover()).
    replace("%backgroundColorBlueNormal%", backgroundColorBlueNormal()).
    replace("%backgroundColorBlueHover%", backgroundColorBlueHover()).
    replace("%backgroundColorBluePressed%", backgroundColorBluePressed()).
    replace("%backgroundColorBlueDisabled%", backgroundColorBlueDisabled()).
    replace("%backgroundColorGrayNormal%", backgroundColorGrayNormal()).
    replace("%backgroundColorGrayHover%", backgroundColorGrayHover()).
    replace("%backgroundColorGrayPressed%", backgroundColorGrayPressed()).
    replace("%backgroundColorGreen%", backgroundColorGreen()).
    replace("%backgroundColorGreenHover%", backgroundColorGreenHover()).
    replace("%backgroundColorAlternate%", backgroundColorAlternate()).
    replace("%borderColor%", borderColor()).
    replace("%borderColorDark%", borderColorDark()).
    replace("%selectionColor%", selectionColor()).
    replace("%statusBarBackgroundColor%", statusBarBackgroundColor()).
    replace("%statusBarFontColor%", statusBarFontColor()).
    replace("%headerBackgroundColor%", headerBackgroundColor()).
    replace("%headerBorderColor%", headerBorderColor()).
    replace("%addressFontColor%", addressFontColor()).
    replace("%balanceFontColor%", balanceFontColor()).
    replace("%toolButtonBackgroundColorNormal%", toolButtonBackgroundColorNormal()).
    replace("%toolButtonBackgroundColorHover%", toolButtonBackgroundColorHover()).
    replace("%toolButtonBackgroundColorPressed%", toolButtonBackgroundColorPressed()).
    replace("%toolButtonFontColorNormal%", toolButtonFontColorNormal()).
    replace("%toolButtonFontColorDisabled%", toolButtonFontColorDisabled()).
    replace("%toolBarBorderColor%", toolBarBorderColor()).
    replace("%glassColor%", glassColor());
}

}
