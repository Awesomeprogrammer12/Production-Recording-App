#ifndef WIDGET_H
#define WIDGET_H
#include "statisticspage.h"
//widgets
#include <QWidget>
#include <QDockWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>
#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QListWidget>
#include <QColorDialog>
#include <QMessageBox> // Optional, if you want "Are you sure?" prompts later
#include <QFontDialog>
#include <QWindow>

//Layouts
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

// file handling
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

//others
#include <Qt>
#include <QSize>
#include <QSettings>
#include <QDebug>
#include <QStringList>
#include <QPixmap>
#include <QIcon>
#include<QDoubleValidator>
#include <QShortcut>
#include <QMouseEvent>
#include <QScrollArea>
#include <QSizeGrip>
#include <QColor>
#include <QTimer>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    struct records
    {
        QString Name;QString Number;QString Category;QString Description;QString Date;
        bool operator==(const records& other) const {
            return Name == other.Name && Number == other.Number &&
                   Category == other.Category && Description == other.Description && Date== other.Date;
        }
        QString& operator[](int index) {
            switch(index) {
            case 0: return Name;
            case 1: return Number;
            case 2: return Category;
            case 3: return Description;
            case 4: return Date;
            default: throw std::out_of_range("Index out of bounds");
            }
        }
    };
    struct TableState {
        QList<records> allRows; // Each QStringList is [Name, Number, Category, Description]
    };

    // Update y


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    QString Theme;
    QList<records> recent;
    QList<TableState> past;
    QList<TableState> future;
    QString Name;QString Number;
    QString Category; QString Description;
    QString Date;
    QString folderName;QString documentsPath ;
    QString fullPath;QString filePath ;
    QString fileName ;QStringList names   =   {};
    QString lambdaVal;
    QString rowName;   QString rowNumb; QString rowCateg; QString rowDescr ;
    int rowIndex ;
    QString bg, btnBg, border, text, accent, hoverBg,fontName1,fontName2;
    QString userbg,userbtnBg,userborder,usertext,useraccent,userhoverBg,userfontName1;
    QString cyberfontName1,cyberfontName2,fontSize,fontSize2;
    int fontSizeInt;int fontSizeInt2;
    int userfontSize;

    QString DeletedName ;
    QString DeletedNumber;
    QString DelCategory ;
    QString DelDescription;

    /* %1=bg,%2btnBg,%3=border,%4=text,
      //%5=accent,%6=hoverBg,%7fontName1,%8fontName2
      %9fontsize,%10fontSize2;*/

    QShortcut* ctrlTabShortcut;
    QShortcut* ctrlShiftTabShortcut;
    QShortcut *undoShortcut;
    QShortcut *redoShortcut;
    QShortcut *enterShortcut;
    QShortcut *windowShortcut1;
    QShortcut *windowShortcut2;

    bool m_resizing = false;
    Qt::WindowFrameSection m_section = Qt::NoSection;
    //master layout
    QWidget *masterWidget;
    QVBoxLayout *master ;

    //NavigationPanel hbox
    QGridLayout *NavigationPanel;

    QHBoxLayout *tabs;
    QPushButton *home;
    QPushButton *store;
    QPushButton *stats;

    QLabel *zion;

    QHBoxLayout *butns;
    QPushButton *minimize;
    QPushButton *maximize;
    QPushButton *exit;

    //main ui
    QStackedWidget *mainui;

    //Main Part grid layout widget: for home menu
    QVBoxLayout *Main;
    QLabel *welcome;
    QLabel *status;// Yu have not added products | Update your records
    QPushButton *add;
    QFrame *NavPanel;
    //Main Part grid widget:: layout for store menu
    QLineEdit *searchDescription;//search Description
    QLineEdit *searchNumber;// search number
    QLineEdit *searchName;// search name
    QLineEdit *searchCategory;// search category
    QPushButton *clr;

    QGridLayout *searchEntrys;
    QHBoxLayout *storeMenu;
    QVBoxLayout *storesSidebar;
    QLabel *prompt;//enter the following to record
    QPushButton *refresh;
    QLabel *namePrompt;
    QLineEdit *name;
    QLabel *numberPrompt;
    QLineEdit *number;
    QLabel *categoriesPrompt;
    QLineEdit *categories;
    QLabel *descriptionPrompt;
    QLineEdit *description;
    QPushButton *Append;//add to the label
    QTableWidget *recordsTabel;

    //bottom-bar
    QHBoxLayout *bottombar;
    QPushButton *settings;
    QLabel *info;
    //settings dialog
    QDialog *settingsDialog;
    QLabel* ApearanceSettings;

    QCheckBox* themeCheck;
    QPushButton *switchTheme;

    QCheckBox *FGroundCheck;
    QPushButton *FGroundEntry;

    QCheckBox* BGroundCheck;
    QPushButton *BGroundEntry;

    QCheckBox *FontCheck;
    QPushButton *FontEntry;

    //edit dialog
    QDialog *editDialog;

    QGridLayout *layout;
    QLabel *promptLabel;
    QLabel *lName;
    QLineEdit *eName;
    QLabel *lNumb;
    QLineEdit *eNumb;
    QLabel *lCateg;
    QLineEdit *eCateg;
    QLabel *lDescr;
    QLineEdit *eDescr;
    QString editStyle;
    QPushButton *saveBtn;

    //mainUI elements
    QWidget* homepage;
    QWidget* storepage;

    void switchThemes(QString &appTheme);//cyberpunk, dark,switch and light
    QString CurrentTab;
    int col;
    //this variable is for settingsDialog
    bool firstTime = true;
    void setActiveTab(QPushButton *activeBtn);
    QTimer *delTimer;//when this timer is done the row of data will be deleted
    void saveCurrentState();
    void saveTable();
    void navigationPanelSetup();
    void mainUISetup();
    void signalSlotsSetup();
public slots:
    void exitWindow();
    void resizeWindow();
    void minimizeWindow();
    void homeTab();
    void storeTab();
    void statsTab();
    void addButton();
    void parser();
    void rerfresher();
    void tableEdited(QTableWidgetItem *item);
    // ... other slots ...
    void updateFilter(); // The new master function
    void switchTabs();
    void switchTabs2();
    void format();
    void deleteRow();
    void showEditDialog();
    void showSettingDialog();
    void delSettingDialog();
    void showColorDialog(QString &value);//if value = fg then open color dialog for font color else bg is background color
    void showFontDialog();
    void lambdaFunctions(QString &value);
    void redoAction();
    void undoAction();
    void enterAction();
    void windowAction1();
    void windowAction2();

private:
    QPoint m_mousePosition;
    bool m_isDragging = false;
    QPoint m_mousePosition2;//for resize
    bool m_isDragging2 = false;//for resize

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
