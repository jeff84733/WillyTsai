#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <qt_windows.h>
#include <conio.h>

#ifndef QString16
#define QString16(x) QString::fromUtf16(reinterpret_cast<const char16_t*>(x))
#endif



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    HANDLE hWindow = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hWindow, &info);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hWindow, FALSE, &cfi);

    qDebug().noquote() << endl << QString16(L"█▇▆▅▄▃▂▁威力彩抽獎機▁▂▃▄▅▆▇█");
    qDebug().noquote() << endl << QString16(L"任意輸入種子號碼，建議10字以上 (號碼可重複，例如 464351897941659794697463315460120)：");
    QString nPocket = "0123456789" +cin.readLine();
    nPocket.remove(QRegExp("[^\\d]"));
    size_t nMax = strlen(nPocket.toLatin1().constData());
    char* nNumbers = new char[nMax];
    memcpy(nNumbers, nPocket.toLatin1().constData(), nMax);

    while(1) {
        qDebug().noquote() << endl << QString16(L"█▇▆▅▄▃▂▁（請按任意鍵繼續）▁▂▃▄▅▆▇█");
        qDebug().noquote() <<  QString16(L"智華老師：「本期開出的號碼是 ......」");
        _getch();
        qDebug().noquote() << endl << QString16(L"第一區號碼：");
        QList<int> random6;
        QString tmpS;
        for(int i=0; i<6; i++) {
            int n = 0;
            while(i >= random6.count()) {
                tmpS.clear();
                tmpS += nNumbers[qrand() %nMax];
                tmpS += nNumbers[qrand() %nMax];
                n = tmpS.toInt();
                if((n>=1) && (n<=38))
                    if(!random6.contains(n))
                        random6.append(n);
            }
        }
        std::sort(random6.begin(), random6.end());
        {
            QString ans;
            for(int i=0; i<6; i++)
                ans += QString::number(random6[i]).rightJustified(2, '0') +", ";
            ans.remove(ans.size() -2, 2);
            qDebug().noquote() << ans;
        }
        qDebug().noquote() << endl << QString16(L"第二區號碼：");
        {
            int n = 0;
            while((n<1) || (n>8)) {
                n = QString(nNumbers[qrand() %nMax]).toInt();
            }
            qDebug().noquote() << QString::number(n).rightJustified(2, '0');
        }

    }

    delete [] nNumbers;
    return a.exec();
}




















