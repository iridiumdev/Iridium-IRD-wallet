#include "QRCodeDialog.h"
#include "qrcodegen.hpp"
#include <QSvgWidget>
#include "ui_qrcodedialog.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace qrcodegen;

namespace WalletGui {

// generate svg qrcode from a string

std::string QRCodeDialog::toSvgString(QrCode qr) const {
    std::ostringstream sb;
    int size = qr.getSize();
    const int border = 2;

    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (size + border * 2) << " " << (size + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}

QRCodeDialog::QRCodeDialog(const QString& _title, const char* _stringToEncode, QWidget* _parent) : QDialog(_parent, static_cast<Qt::WindowFlags>(Qt::WindowCloseButtonHint)),
    m_ui(new Ui::QRCodeDialog) {
    QSvgWidget* svgWidget(new QSvgWidget(this));
    m_ui->setupUi(this);
    m_ui->m_qrLabel->setText(_title);
    m_svg = toSvgString(QrCode::encodeText(_stringToEncode, QrCode::Ecc::QUARTILE));
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
