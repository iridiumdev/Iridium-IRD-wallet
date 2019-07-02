#include "QRCodeDialog.h"
#include "QrCode.hpp"
#include <QSvgWidget>
#include "ui_qrcodedialog.h"

#include <iostream>

using namespace qrcodegen;

namespace WalletGui {

// generate svg qrcode from a string

QRCodeDialog::QRCodeDialog(const QString& _title, const char* _stringToEncode, QWidget* _parent) : QDialog(_parent, static_cast<Qt::WindowFlags>(Qt::WindowCloseButtonHint)),
    m_ui(new Ui::QRCodeDialog) {
    QSvgWidget* svgWidget(new QSvgWidget(this));
//    setWindowTitle(_title);
    m_ui->setupUi(this);
    m_ui->m_qrLabel->setText(_title);
    QrCode qr0 = QrCode::encodeText(_stringToEncode, QrCode::Ecc::QUARTILE);
    m_svg = qr0.toSvgString(4);
    svgWidget->load(QByteArray(m_svg.c_str(),m_svg.length()));
    svgWidget->setBaseSize(1000,1000);
    svgWidget->setGeometry(0,0,500,500);
    svgWidget->show();
}

QRCodeDialog::~QRCodeDialog(){
}

std::string QRCodeDialog::getSvg(){
    return m_svg;
}

void QRCodeDialog::qrClicked(){
std::cout << "QR clicked" << std::endl;
}

}
