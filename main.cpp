#include <QApplication>

#include "Method.h"
#include "mainwindow.h"
#include "myapp.h"

void loadLocal();
extern QVector<QString> filelist;
QWidgetList wdlist;
extern QString PlistFileName, CurVersion, ocVer;
extern bool zh_cn;
MainWindow *mw_one;

int main(int argc, char *argv[]) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
  {
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  }
#endif

  MyApplication *a = new MyApplication(argc, argv);
#ifdef Q_OS_MAC
  Method::init_MacVerInfo(CurVersion);
#endif
  loadLocal();

  QString strAppExePath = qApp->applicationDirPath();
  mw_one->copyDirectoryFiles(strAppExePath + "/Database/",
                             QDir::homePath() + "/Database/", false);
  QDir dir;
  QString strDrivers0 = strAppExePath + "/Database/EFI/OC/Drivers/";
  QString strTools0 = strAppExePath + "/Database/EFI/OC/Tools/";
  QString strDrivers1 = QDir::homePath() + "/Database/EFI/OC/Drivers/";
  QString strTools1 = QDir::homePath() + "/Database/EFI/OC/Tools/";
  QString strDrivers2 = QDir::homePath() + "/devDatabase/EFI/OC/Drivers/";
  QString strTools2 = QDir::homePath() + "/devDatabase/EFI/OC/Tools/";
  QString strDrivers3 = QDir::homePath() + "/Database/DEBUG/EFI/OC/Drivers/";
  QString strTools3 = QDir::homePath() + "/Database/DEBUG/EFI/OC/Tools/";
  QString strDrivers4 = QDir::homePath() + "/devDatabase/DEBUG/EFI/OC/Drivers/";
  QString strTools4 = QDir::homePath() + "/devDatabase/DEBUG/EFI/OC/Tools/";
  dir.mkpath(strDrivers1);
  dir.mkpath(strTools1);
  dir.mkpath(strDrivers2);
  dir.mkpath(strTools2);
  dir.mkpath(strDrivers3);
  dir.mkpath(strTools3);
  dir.mkpath(strDrivers4);
  dir.mkpath(strTools4);
  QStringList listDrivers, listTools;
  listDrivers = Method::DirToFileList(strDrivers0, "*.efi");
  listTools = Method::DirToFileList(strTools0, "*.efi");
  for (int i = 0; i < listDrivers.count(); i++) {
    mw_one->copyFileToPath(strDrivers0 + listDrivers.at(i),
                           strDrivers1 + listDrivers.at(i), false);
    mw_one->copyFileToPath(strDrivers0 + listDrivers.at(i),
                           strDrivers2 + listDrivers.at(i), false);
    mw_one->copyFileToPath(strDrivers0 + listDrivers.at(i),
                           strDrivers3 + listDrivers.at(i), false);
    mw_one->copyFileToPath(strDrivers0 + listDrivers.at(i),
                           strDrivers4 + listDrivers.at(i), false);
  }
  for (int i = 0; i < listTools.count(); i++) {
    mw_one->copyFileToPath(strTools0 + listTools.at(i),
                           strTools1 + listTools.at(i), false);
    mw_one->copyFileToPath(strTools0 + listTools.at(i),
                           strTools2 + listTools.at(i), false);
    mw_one->copyFileToPath(strTools0 + listTools.at(i),
                           strTools3 + listTools.at(i), false);
    mw_one->copyFileToPath(strTools0 + listTools.at(i),
                           strTools4 + listTools.at(i), false);
  }

  QString fileSample =
      QDir::homePath() + "/Database/BaseConfigs/SampleCustom.plist";
  if (!QFile(fileSample).exists()) {
    QMessageBox::critical(
        NULL, "",
        fileSample + "\n\n" +
            QObject::tr("The file does not exist, please check the "
                        "integrity of the app."));

    return 0;
  }

  QFont f;
#ifdef Q_OS_WIN32

  PlistFileName = QString::fromLocal8Bit(argv[1]);  //解决乱码

  f.setFamily("Microsoft YaHei UI");

#endif

#ifdef Q_OS_MAC

#endif

  if (!PlistFileName.isEmpty()) {
    a->new_win();
  } else {
    mw_one = new MainWindow();
    mw_one->show();
  }

  f.setPixelSize(12);
  a->setFont(f);
  return a->exec();
}

void loadLocal() {
  static QTranslator translator;
  static QTranslator translator1;
  static QTranslator translator2;

  QLocale locale;
  if (locale.language() == QLocale::English) {
    zh_cn = false;

  } else if (locale.language() == QLocale::Chinese) {
    bool tr = false;
    tr = translator.load(":/cn.qm");
    if (tr) {
      qApp->installTranslator(&translator);
      zh_cn = true;
    }

    bool tr1 = false;
    tr1 = translator1.load(":/qt_zh_CN.qm");
    if (tr1) {
      qApp->installTranslator(&translator1);
      zh_cn = true;
    }

    bool tr2 = false;
    tr2 = translator2.load(":/widgets_zh_cn.qm");
    if (tr2) {
      qApp->installTranslator(&translator2);
      zh_cn = true;
    }

    // ui->retranslateUi(this);
  }
}
