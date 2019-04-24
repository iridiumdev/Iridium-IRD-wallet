// Copyright (c) 2019, The Iridium developer
//
// This file is part of Iridium.
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#include "WalletSmallButton.h"
#include "Settings/Settings.h"
#include "Style/Style.h"
namespace WalletGui {
    namespace {

    const char WALLET_SMALL_BUTTON_STYLE_SHEET_TEMPLATE[] =
      "* {"
        "font-family: %fontFamily%;"
      "}"

      "WalletGui--WalletSmallButton {"
        "min-width: 32px;"
        "max-width: 32px;"
        "min-height: 32px;"
        "max-height: 32px;"
        "font-size: %fontSizeNormal%;"
        "background-color: #dddddd;"
        "border: 0px;"
      "}"

      "WalletGui--WalletSmallButton:disabled {"
        "border: 0px;"
      "}"

      "WalletGui--WalletSmallButton:hover {"
        "border: 1px solid #333333;"
      "}"

      "WalletGui--WalletSmallButton:pressed {"
        "color: #ffffff;"
        "border: 1px solid #dddddd;"
      "}";

    }

WalletSmallButton::WalletSmallButton(QWidget* _parent) : QPushButton(_parent) {
    setStyleSheet(Settings::instance().getCurrentStyle().makeStyleSheet(WALLET_SMALL_BUTTON_STYLE_SHEET_TEMPLATE));
}

WalletSmallButton::~WalletSmallButton(){
}

}
