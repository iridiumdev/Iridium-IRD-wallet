// Copyright (c) 2019, The Iridium developer
//
// This file is part of Iridium.
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include <QPushButton>

namespace WalletGui {


class WalletSmallButton : public QPushButton {
    Q_OBJECT
    Q_DISABLE_COPY(WalletSmallButton)

public:
    explicit WalletSmallButton(QWidget* _parent);
    ~WalletSmallButton();
};

}
