
#pragma once

#include <QDialog>
#include "QrCode.hpp"

namespace Ui {
class QRCodeDialog;
}


namespace WalletGui {

class QRCodeDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(QRCodeDialog)

public:
    QRCodeDialog(const QString& _title, const char* _text, QWidget* _parent);
    ~QRCodeDialog();
    std::string getSvg();

private:
    QScopedPointer<Ui::QRCodeDialog> m_ui;
    std::string m_svg;
    Q_SLOT void qrClicked();
};

}
