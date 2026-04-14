#include "widget.h"
#include <QHeaderView> // Needed for stretching the table
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("this"); //i set this to this not this to that isnt that genius

    setMouseTracking(true);
    // --- FIX 1: Resource Path Correction (iimages) ---
    setWindowIcon(QIcon(":/images/Zions.png"));
    //setWindowTitle(Zion:production records app
    setAutoFillBackground(true);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Window  | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint|Qt::WindowTitleHint);
    this->setFocusPolicy(Qt::StrongFocus);
    ctrlTabShortcut = new QShortcut(QKeySequence::NextChild, this);
    ctrlShiftTabShortcut = new QShortcut(QKeySequence("Ctrl+Shift+Tab"), this);

    undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"),this);
    redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"),this);
    enterShortcut = new QShortcut(QKeySequence("Return"),this);
    windowShortcut1 = new QShortcut(QKeySequence("Alt+Left"), this);
    windowShortcut1->setContext(Qt::ApplicationShortcut);

    windowShortcut2 = new QShortcut(QKeySequence("Alt+Right"), this);
    windowShortcut2->setContext(Qt::ApplicationShortcut);
    Theme = "dark";

    // Variables
    // --- FIX 2: Added "Action" to headers for the Delete button ---
    QStringList header = {"Name", "Number", "Category", "Description","TimeStamp", "Action"};

    folderName = "/Production Records app/";
    documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    fileName = "data.records";
    fullPath = documentsPath + folderName;
    filePath = fullPath + fileName;

    setWindowFilePath(fullPath);

    master = new QVBoxLayout();

    navigationPanelSetup();

    mainUISetup();

    StatisticsPage *statsPage = new StatisticsPage(this);

    // 1. Setup the Layout Container
    QWidget* recordsTabelWidget = new QWidget();
    QGridLayout* recordsTabelLayout = new QGridLayout(recordsTabelWidget);
    searchEntrys = new QGridLayout(); // Removed 'this'
    searchName = new QLineEdit(this);
    searchNumber = new QLineEdit(this);
    searchCategory = new QLineEdit(this);
    searchDescription = new QLineEdit(this);
    clr = new QPushButton(this);

    recordsTabel = new QTableWidget(this);
    recordsTabelLayout->setAlignment(Qt::AlignTop);
    recordsTabelLayout->setContentsMargins(0, 0, 0, 0);
    recordsTabelLayout->setSpacing(0); // Optional: removes space between search and table
    recordsTabelLayout->addLayout(searchEntrys, 0, 0, 1, 2);
    recordsTabelLayout->addWidget(recordsTabel, 1, 0, 6, 6);
    recordsTabelLayout->setRowStretch(1, 1);
    searchEntrys->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    searchName->setPlaceholderText("🔎Filter-Name");
    searchNumber->setPlaceholderText("🔎Number");
    searchCategory->setPlaceholderText("🔎Categories");
    clr->setText("Clear");
    clr->setObjectName("clr");
    searchDescription->setPlaceholderText("🔎Descriptions");

    searchName->setObjectName("search");
    searchNumber->setObjectName("search");
    searchCategory->setObjectName("search");
    searchDescription->setObjectName("search");
    searchName->setToolTip("filter-name");
    searchNumber->setToolTip("filter-number");
    searchCategory->setToolTip("filter-category");
    searchDescription->setToolTip("filter-description");

    home->setFocusPolicy(Qt::NoFocus);
    store->setFocusPolicy(Qt::NoFocus);
    stats->setFocusPolicy(Qt::NoFocus);

    prompt->setText("Fill the following information");
    prompt->setStyleSheet("font-family:Comic Sans MS;font-size:18px");
    namePrompt->setText("Enter name of item:");
    namePrompt->setObjectName("prompt");
    numberPrompt->setText("Enter amount of item:");
    numberPrompt->setObjectName("prompt");
    categoriesPrompt->setText("Enter the category of item:");
    categoriesPrompt->setObjectName("prompt");
    descriptionPrompt->setText("Describe the item");
    descriptionPrompt->setObjectName("prompt");
    Append->setText("ADD");
    Append->setObjectName("Append");

    refresh->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::ViewRestore)); // Path fix
    refresh->setIconSize(QSize(27, 27));
    refresh->setFixedSize(50, 50);
    refresh->setStyleSheet("border-radius:10px;border:none;");

    recordsTabel->setRowCount(0); // Start empty
    recordsTabel->setColumnCount(6); // Increased to 6 for "TimeStamp"
    recordsTabel->setColumnHidden(4, true);//hide only timestamps column
    recordsTabel->setHorizontalHeaderLabels(header);

    recordsTabel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    recordsTabel->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Fixed);

    recordsTabel->setFont(QFont("consolas", 11, 4, true));
    recordsTabel->setAutoFillBackground(true);
    recordsTabel->setFocusPolicy(Qt::NoFocus);

    // Bottom Bar
    QWidget* bottombarWidget = new QWidget();
    bottombar = new QHBoxLayout(bottombarWidget);
    settings = new QPushButton();
    settings->setObjectName("btm");
    info = new QLabel();
    info->setObjectName("btm");

    bottombarWidget->setObjectName("bottomBarWidget");
    bottombar->setContentsMargins(7, 7, 7, 7);
    info->setText("You haven't added anything please add...");
    settings->setIcon(QIcon::fromTheme("preferences-system"));; // Path fix
    settings->setIconSize(QSize(32, 32));
    bottombar->setAlignment(Qt::AlignBottom);
    info->setAlignment(Qt::AlignRight);

    // Adding widgets
    mainui->addWidget(homepage);
    mainui->addWidget(storepage);
    mainui->addWidget(statsPage);
    mainui->setCurrentIndex(0);

    tabs->addWidget(home, 0, Qt::AlignBottom);
    tabs->addWidget(store, 0, Qt::AlignBottom);
    tabs->addWidget(stats, 0, Qt::AlignBottom);

    searchEntrys->addWidget(searchName, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignTop);
    searchEntrys->addWidget(searchNumber, 0, 1, 1, 1, Qt::AlignRight | Qt::AlignTop);
    searchEntrys->addWidget(searchCategory, 0, 2, 1, 1, Qt::AlignRight | Qt::AlignTop);
    searchEntrys->addWidget(searchDescription, 0, 3, 1, 1, Qt::AlignRight | Qt::AlignTop);
    searchEntrys->addWidget(clr, 0, 4, 1, 1, Qt::AlignTop);

    butns->addWidget(minimize, 0, Qt::AlignRight);
    butns->addWidget(maximize, 0, Qt::AlignRight);
    butns->addWidget(exit, 0, Qt::AlignRight);

    Main->addWidget(welcome, 1, Qt::AlignTop);
    Main->addWidget(status, 3, Qt::AlignCenter);
    Main->addWidget(add, 3, Qt::AlignCenter);

    storesSidebar->addWidget(refresh, 1, Qt::AlignTop);
    storesSidebar->addWidget(prompt, 1, Qt::AlignTop);
    storesSidebar->addWidget(namePrompt, 1, Qt::AlignTop);
    storesSidebar->addWidget(name, 1, Qt::AlignTop);
    storesSidebar->addWidget(numberPrompt, 1, Qt::AlignTop);
    storesSidebar->addWidget(number, 1, Qt::AlignTop);
    storesSidebar->addWidget(categoriesPrompt, 1, Qt::AlignTop);
    storesSidebar->addWidget(categories, 1, Qt::AlignTop);
    storesSidebar->addWidget(descriptionPrompt, 1, Qt::AlignTop);
    storesSidebar->addWidget(description, 1, Qt::AlignTop);
    storesSidebar->addWidget(Append, 1, Qt::AlignTop);

    recordsTabelLayout->addLayout(searchEntrys, 0, 0, 1, 6);

    // --- FIX 5: Layout Alignment ---
    // Removed Qt::AlignBottom so the table expands vertically
    recordsTabelLayout->addWidget(recordsTabel, 1, 0, 6, 6);

    NavigationPanel->addLayout(tabs, 0, 0, 1, 2, Qt::AlignLeft | Qt::AlignBottom);
    NavigationPanel->addWidget(zion, 0, 4, 1, 2, Qt::AlignCenter | Qt::AlignVCenter);
    NavigationPanel->addLayout(butns, 0, 6, 0, 2, Qt::AlignRight | Qt::AlignTop);

    bottombar->addWidget(settings, 1, Qt::AlignLeft);
    bottombar->addWidget(info, 1, Qt::AlignRight);

    storesSidebar->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    storeMenu->addLayout(storesSidebar, 2);
    storeMenu->addWidget(recordsTabelWidget, 6);

    master->addWidget(NavPanel, 0);
    master->addWidget(mainui, 1);
    master->addWidget(bottombarWidget, 0);

    // Connections
    signalSlotsSetup();

    clr->setToolTip("Clear Search input fields");
    number->setValidator(new QDoubleValidator(0.5, 1000000, 1, this));
    setWindowOpacity(0.99);
    setLayout(master);
    if (mainui->currentIndex() == 0) homeTab();
    else if (mainui->currentIndex() == 1) storeTab();

    parser(); // Load data

    info->setAutoFillBackground(true);
    info->setAlignment(Qt::AlignLeft);
    Theme = "dark";
    switchThemes(Theme);
    userfontSize = 10;

}

Widget::~Widget()
{
    this->close();
    qInfo()<<"finished with exec code 0";
}
void Widget::switchThemes(QString &appTheme)
{
    //some variables like border widths cant be stored and are unique
    fontName1 = "consolas";
    fontName2 = "comic-sans";

    fontSizeInt =   15;
    fontSizeInt2 = 25;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ;
    //only custom theme(user theme) and cyberpunk can change font

    if (appTheme == "switch"){
        if(Theme == "white"){
            Theme = "dark";
        }else if(Theme == "dark"){
            Theme = "cyberpunk";
        }else if (Theme == "cyberpunk"){
            Theme = "custom";
        }else{
            Theme = "white";
        }
    }else if (appTheme == "refresh") {
        qInfo()<<"forgot hw to do nothing";
    }else{
        Theme = appTheme.isEmpty() ? "dark" : appTheme;
    }
    if(Theme == "custom"){
        bg = userbg.isEmpty() ? "#1f1f1f": userbg; border = userborder.isEmpty() ? "gold" : userborder; text = usertext.isEmpty() ? "white":usertext; accent = useraccent.isEmpty()?"#aa1293": useraccent;btnBg = userbtnBg.isEmpty() ? "#3f3f3f" : userbtnBg;fontName1 = userfontName1.isEmpty() ? fontName1 : userfontName1;fontSizeInt = userfontSize == 0 ? fontSizeInt : userfontSize;
    }else if (Theme == "cyberpunk") {
        bg = "#050505"; border = "#00ffff"; text = "#00ffff"; accent = "#00ff00"; hoverBg = "#002222";btnBg = "#0000ff";fontName1 = cyberfontName1.isEmpty() ? fontName1 : cyberfontName1;fontName2 = cyberfontName2.isEmpty() ? fontName2 : cyberfontName2;
    } else if (Theme == "white") {
        bg = "white"; border = "yellow";      text = "#0f1f0f";     accent = "#f2b7a7"; hoverBg = "gray";btnBg = "#e4e4e4";
    } else { // Default Dark
        bg = "#1f1f1f"; border = "gold";      text = "white";     accent = "#aa1293"; hoverBg = "#8d8d8d";btnBg = "#3f3f3f";
    }

    // 2. The Master Template with ALL your object names restored
    // %1=bg,%2btnBg,%3=border,%4=text, %5=accent,%6=hoverBg,%7fontName1,%8fontName2;
    fontSize = QString::number(fontSizeInt)+"px";
    fontSize2 = QString::number(fontSizeInt2)+"px";
    QString masterStyle = R"(
            /* Global & Master Widget */
            * { color: %4;background-color:%1; }

            QWidget#tabstack{
                  border:5px solid green;
            }
            /*this is not the master widget just a widget i added before adding anything so it can be a margin linge*/
            QWidget#masterWidget {
                  background-color: %1;
                  border:3px solid %5;
            }QWidget#NavigationalWidget{
                  background-color:%2;
                  border-radius:7px;
                  font-family:%7;
                  color:%4;
            }
            /* Standard Buttons */
            QPushButton {
                  background-color: %2;
                  border: 3px solid %3;
                  border-radius: 25px;
                  font-weight: bolder;
                  font-family:%7;
                  height: 35px; width: 70px;
            }
            QPushButton:hover { background-color: %5; color: %4; border-color: %6; padding: 20px; }
            QPushButton:pressed { background-color: #AA1923; border: 5px solid %2; }

            /* Specific IDs */
            QPushButton#tabButtons { border-top-left-radius: 10px; border-top-right-radius: 10px; }
            QPushButton#append { border-width: 5px; border-radius: 25px; padding: 50px; }
            QPushButton#clr {background-color: %2; border: 2px solid %4; border-radius: 3px; height: 20px;}
            QPushButton#clr:hover { background-color: %5; border-color: violet; width: 95px; }
            /* Labels */
            QLabel{font-size: %9; font-weight: bolder;}
            QLabel#welcome { font-family: %8; font-size: %10; color: %4; }
            QLabel#prompt { color:%4;font-size:%9; }

            /* Input Fields */
            QLineEdit {
                  background-color: %2; border: 3px solid %5;height:40px; border-radius: 6px; color: #ffd700; font-size:25px;
            }
            QLineEdit#search {color:%4;height:20px;font-size:%9;/*font is too small to record with a variable*/ }
            QLineEdit:hover { border: 1px solid yellow; padding: 5px; }

            /* Table & Scroll */
            QTableWidget { background-color: %2; gridline-color: %5; font-size: %9; }
            QHeaderView::section { background-color:%1; font-size: %9; }
            QScrollBar:vertical { background: %1; width: 15px; }
            QWidget#bottomBarWidget{border:2px solid %5;background-color:%2;height:45px}
            QPushButton#btm{border:2px solid %6;border-radius:5px;height:40px}
            QPushButton#tabButtons{width:80px;font-size:10;}
            QLabel#btm{border:2px solid %6;height:50px;background-color:%2}
            QLabel#Zion{border:none;background-color:%2;color:#FeFeFe;}
            QPushButton::focus{border-width:2px;outline:none;border-style: dashed;}
            QLineEdit::focus{border-width:2px;outline:none;border-style: dashed;
      )";
    // 3. Apply everything in one sh
    this->setStyleSheet(masterStyle.arg(bg,btnBg,border,text,accent,hoverBg,fontName1,fontName2,fontSize,fontSize2));
}

void Widget::setActiveTab(QPushButton *activeBtn) {
    QString Them = "refresh";
    home->setStyleSheet("background-color:"+bg+";color:"+text+";border-color:"+btnBg);
    store->setStyleSheet("background-color:"+bg+";color:"+text+";border-color:"+btnBg);
    stats->setStyleSheet("background-color:"+bg+";color:"+text+";border-color:"+btnBg);

    activeBtn->setStyleSheet("background-color:"+hoverBg+";color:"+text+";border-color:"+hoverBg);
}

void Widget::exitWindow(){ this->close(); }
void Widget::resizeWindow(){ if(!isMaximized()){showMaximized();return;} showNormal(); }
void Widget::minimizeWindow(){ showMinimized(); }

void Widget::homeTab()
{
    zion->setText("Zion:home");
    setActiveTab(home);
    CurrentTab = "Home";
    mainui->setCurrentIndex(0);

}
void Widget::storeTab()
{
    zion->setText("Zion:store");
    setActiveTab(store);
    CurrentTab = "Store";
    mainui->setCurrentIndex(1);
}
void Widget::statsTab()
{
    zion->setText("Zion:Stats");
    setActiveTab(stats);
    CurrentTab = "Stats";
    mainui->setCurrentIndex(2);
}

void Widget::addButton()
{
    saveCurrentState();
    Name = name->text().trimmed();
    Number = number->text().trimmed();
    Category = categories->text().trimmed();
    Description = description->text().trimmed();
    Date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    qInfo()<<"Saved Current status";
    if (Name.isEmpty() || Number.isEmpty() || Category.isEmpty()){
        QMessageBox::warning(this, "Warning", "Fill Empty Field(s)");
        return;
    }
    if (Name.length() > 20 || Category.length() > 20) {
        name->setPlaceholderText("Too long (>20 chars)");
        info->setText("Name Too long (>20 chars)");
        return;
    }
    static QRegularExpression re("^[0-9.]+$");
    if (!re.match(Number).hasMatch() || Number == "0") {
        number->setPlaceholderText("Must be a digit/decimal > 0");
        info->setText("Number Must be a digit > 0");
        return;
    }
    if (names.contains(Name)) {
        QMessageBox::warning(this, "Warning", "Name Already Exists.");
        name->setPlaceholderText("Name already exists");
        info->setText("Name already exists");
        return;
    }
    Name.replace("\"","'");
    Number.replace("\"","'");
    Category.replace("\"","'");
    Description.replace("\"","'");

    qInfo()<<"Formated:\n\tname:"<<Name<<"\n\tnumber:"<<Number;

    QDir().mkpath(fullPath);
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text) ) {
        return;
    }
    qInfo()<<"Opened Path"<<filePath;
    QTextStream stream(&file);
    QString fullFile;
    QString today;
    QString todayHeader;
    QString content ;
    QString newContent;
    QString todayContent;
    today = QDate::currentDate().toString("yyyy-MM-dd");
    todayHeader = "[" + today + "]{";
    fullFile = stream.readAll();
    if(fullFile.startsWith(todayHeader)){
        int start  = fullFile.indexOf("{");
        int end = fullFile.indexOf("}");\
        newContent ="\n-new\nN:\"" + Name + "\"\nI:\"" + Number+ "\"\nC:\"" + Category + "\"\nD:\"" + Description + "\"\nT:\""+Date+"\"\n";
        fullFile.insert(end-1,newContent);
        file.seek(0);
        file.resize(0);
        stream.seek(0);
        stream << fullFile;
        status->setText(QString("Added: %1, (%2)").arg(Name, Category));
    }
    else if(fullFile.startsWith("[")&&fullFile.endsWith("{")){
        int start = fullFile.indexOf("{");
        int end = fullFile.indexOf("}");
        content = fullFile.mid(start + 1, end - start - 1);
        newContent = content +"\n-new\nN:\"" + Name + "\"\nI:\"" + Number+ "\"\nC:\"" + Category + "\"\nD:\"" + Description + "\"\nT:\""+Date+"\"";
        todayContent = todayHeader+"\n"+newContent+"}";
        fullFile.prepend(todayContent);
        file.seek(0);
        file.resize(0);
        stream.seek(0);
        stream << fullFile;
    }
    else if(!fullFile.startsWith("[")||fullFile.isEmpty()){
        qInfo()<<"empty";
        file.seek(0);
        file.resize(0);
        newContent = "-new\nN:\"" + Name + "\"\nI:\"" + Number+ "\"\nC:\"" + Category + "\"\nD:\"" + Description + "\"\nT:\""+Date+"\"\n";
        todayContent = todayHeader+"\n"+newContent+"}";
        file.seek(0);
        file.resize(0);
        stream.seek(0);
        stream << todayContent;
    }
    stream.flush();
    file.close();
    parser();
    for (auto edts: {name,number,categories,description}){
        edts->setText("");
        edts->setPlaceholderText("");
    }
    saveCurrentState();
}

// --- turns file to table
void Widget::parser()
{

    recordsTabel->setRowCount(0);
    names.clear();
    recent.clear();

    disconnect(recordsTabel, &QTableWidget::itemChanged, this, &Widget::tableEdited);
    this->blockSignals(true);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        connect(recordsTabel, &QTableWidget::itemChanged, this, &Widget::tableEdited);
        this->blockSignals(false);
        return;
    }

    QString todayHeader = "[" + QDate::currentDate().toString("yyyy-MM-dd") + "]{";
    QString fullFile = file.readAll();
    file.close();

    // Fix: Instead of reading the stream again, we use the string we already have
    QStringList lines = fullFile.split('\n');
    int currentRow = -1;
    bool insideToday = false;

    for (QString line : lines) {
        line = line.trimmed();
        if (line.isEmpty()) continue;

        if (line.startsWith(todayHeader)) {
            insideToday = true;
            continue;
        }else if(line.startsWith("[")&&line.endsWith("{")){
            int start = fullFile.indexOf("{");
            int end = fullFile.indexOf("}");
            QString content = fullFile.mid(start + 1, end - start - 1);
            fullFile.prepend(todayHeader+content+"}\n");
            file.close();
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                connect(recordsTabel, &QTableWidget::itemChanged, this, &Widget::tableEdited);
                this->blockSignals(false);
                return;
            }
            QTextStream out(&file);
            out.seek(0);
            file.seek(0);
            file.resize(0);
            out<<fullFile;
            connect(recordsTabel, &QTableWidget::itemChanged, this, &Widget::tableEdited);
            this->blockSignals(false);
            file.close();
            parser();
            return;
        }
        // If we hit the end of the today block, STOP.
        // This ensures ONLY today is shown.
        if (line == "}") {
            if (insideToday) break;
            continue;
        }

        if (insideToday) {
            if (line.startsWith("-new")) {
                currentRow++;
                recordsTabel->insertRow(currentRow);
                // ... (Button Creation Logic Here) ...
                QWidget *tabelwidgets = new QWidget(this);
                QPushButton* deleteBtn = new QPushButton("DEl",tabelwidgets);
                QPushButton* editButtn = new QPushButton("EDIT",tabelwidgets);
                editButtn->setGeometry(50,0,50,30);
                deleteBtn->setFixedSize(50, 30);
                editButtn->setFixedSize(50,30);
                editButtn->setToolTip("Edit this row");
                deleteBtn->setToolTip("Delete this row");
                editButtn->setCursor(Qt::PointingHandCursor);
                deleteBtn->setCursor(Qt::PointingHandCursor);

                editButtn->setObjectName("tabelbtn");
                deleteBtn->setObjectName("tabelbtn");

                deleteBtn->setProperty("row",currentRow);
                editButtn->setProperty("row",currentRow);

                QString stylesheetsd = R"(QPushButton#tabelbtn{font-size:10px;font-weight:bold;color:green;})";
                QString editButtnsheet= "background-color:yellow;";
                QString delSheet = "background-color:red;";

                editButtn->setStyleSheet(stylesheetsd+editButtnsheet);deleteBtn->setStyleSheet(stylesheetsd+delSheet);
                // Connect to our new delete logic
                connect(editButtn,   &QPushButton::clicked ,this,&Widget::showEditDialog);
                connect(deleteBtn, &QPushButton::clicked, this, &Widget::deleteRow);
                // Add to column 4(action)
                recordsTabel->setCellWidget(currentRow,5,tabelwidgets);
                records newEntry;
                recent.prepend(newEntry);
            }
            else if (currentRow >= 0) {
                QString val = line.mid(2).remove('"');
                if (line.startsWith("N:")) {
                    recordsTabel->setItem(currentRow, 0, new QTableWidgetItem(val));
                    names.append(val);
                    recent[0][0]= val;
                }
                else if (line.startsWith("I:")) {
                    recordsTabel->setItem(currentRow, 1, new QTableWidgetItem(val));
                    recent[0][1] = val;
                }
                else if (line.startsWith("C:")) {
                    recordsTabel->setItem(currentRow, 2, new QTableWidgetItem(val));
                    recent[0][2] = val;
                }
                else if (line.startsWith("D:")) {
                    recordsTabel->setItem(currentRow, 3, new QTableWidgetItem(val));
                    recent[0][3] = val;
                }
                else if (line.startsWith("T:")) {
                    recordsTabel->setItem(currentRow, 4, new QTableWidgetItem(val));
                    recent[0][4] = val;
                }
            }
        }
    }

    // ... (Keep your formatting/Recent-list logic here) ...
    QString listStr = "Recents:\n";
    for (int i = 0; i < recent.size(); ++i) {
        if(recent.size()>2){
            recent.pop_back();
        }
        listStr += QString("Name: %1 Number: %2 Category: %3 Description: %4 \n").arg(recent[i].Name,recent[i].Number ,recent[i].Category, recent[i].Description);
    }
    info->setText(listStr);
    status->setText(listStr);

    for (int row = 0; row < recordsTabel->rowCount(); ++row) {
        for (int col = 0; col < recordsTabel->columnCount(); ++col) {
            // Skip the Action column (4)
            if (col == 4) continue;

            QTableWidgetItem *item = recordsTabel->item(row, col);
            if (item) {
                if (col == 3) item->setFlags(item->flags() | Qt::ItemIsEditable);
                else item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }if (recordsTabel->rowCount() == 0) {
        // If no records were added, change the label text
        info->setText("You haven't added anything yet. Please add a record!");
        status->setText("You haven't added anything yet. Please add a record!");
        info->setStyleSheet("color: #888888; font-style: italic;"); // Make it look like a hint
    }else{
        info->setStyleSheet("color:white,font-style:consolas");
    }
    this->blockSignals(false);
    connect(recordsTabel, &QTableWidget::itemChanged, this, &Widget::tableEdited);
    saveCurrentState();
}

void Widget::rerfresher()
{
    QString them = "switch";
    blockSignals(true);
    parser();
    QTimer *timer = new QTimer(this);
    timer->singleShot(200, this,[this,them]{this->setWindowOpacity(0.98);switchThemes(Theme);});
    setWindowOpacity(0.85);
    this->setStyleSheet("background-color:"+bg+";");
    timer->start();
    blockSignals(false);
}

void Widget::tableEdited(QTableWidgetItem *item)
{

    //to prevent an infinite call back loop my block signals
    blockSignals(true);
    // another 'itemChanged' signal while we are processing.
    recordsTabel->blockSignals(true);
    saveTable();
    // We don't necessarily need to re-parse the whole file after an edit,
    // but it keeps things consistent with your original logic.
    parser();
    blockSignals(false);
    recordsTabel->blockSignals(true);

}

//search the table
void Widget::updateFilter()
{
    QString nKey = searchName->text().trimmed();
    QString iKey = searchNumber->text().trimmed();
    QString cKey = searchCategory->text().trimmed();
    QString dKey = searchDescription->text().trimmed();

    for (int row = 0; row < recordsTabel->rowCount(); ++row) {

        // Safety check
        if(!recordsTabel->item(row, 0)) continue;

        QString nameCell = recordsTabel->item(row, 0)->text();
        QString numCell   = recordsTabel->item(row, 1)->text();
        QString catCell   = recordsTabel->item(row, 2)->text();
        QString descCell = recordsTabel->item(row, 3)->text();

        bool nameMatch = nKey.isEmpty() || nameCell.contains(nKey, Qt::CaseInsensitive);
        bool numMatch   = iKey.isEmpty() || numCell.contains(iKey, Qt::CaseInsensitive);
        bool catMatch   = cKey.isEmpty() || catCell.contains(cKey, Qt::CaseInsensitive);
        bool descMatch = dKey.isEmpty() || descCell.contains(dKey, Qt::CaseInsensitive);

        if (nameMatch && numMatch && catMatch && descMatch) {
            recordsTabel->showRow(row);
        } else {
            recordsTabel->hideRow(row);
        }
    }
}

void Widget::switchTabs()
{
    if (CurrentTab == "Home"){
        storeTab();
    }else if(CurrentTab == "Store"){
        statsTab();
    }else if(CurrentTab == "Stats"){
        homeTab();
    }
}

void Widget::switchTabs2()
{
    qInfo()<<"ctrl shift Tab";
    if (CurrentTab == "Stats"){
        storeTab();
    }else if(CurrentTab == "Store"){
        homeTab();
    }else if(CurrentTab == "Home"){
        statsTab();
    }

}


void Widget::format()
{
    searchName->clear();
    searchNumber->clear();
    searchDescription->clear();
    searchCategory->clear();
    // After clearing search, show all rows again
    updateFilter();
}

void Widget::deleteRow() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Delete Item",
                                 "Are you sure you want to delete this item?",
                                 QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Perform deletion
        qDebug() << "Item deleted";
    } else {
        // Cancel deletion
        qDebug() << "Delete cancelled";
        return;
    }
    saveCurrentState();
    for(auto searches: {searchName,searchNumber,searchCategory,searchDescription}){
        searches->setText("");
    }

    // 1. Get the button's parent (the QWidget container)
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    // 2. Find the row index using the CONTAINER, not the button

    int rowToRemove = btn->property("row").toInt();
    if (rowToRemove != -1) {
        names.removeOne(recordsTabel->item(rowToRemove,0)->text());//update names list
        recordsTabel->removeRow(rowToRemove);
        tableEdited(nullptr); // Save changes to file
    }
    saveCurrentState();

}

void Widget::showEditDialog()
{
    for(auto searches: {searchName,searchNumber,searchCategory,searchDescription}){
        searches->setText("");
    }
    qInfo()<<"Edit dialog starting";
    recordsTabel->blockSignals(true);
    saveCurrentState();
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) {
        qInfo()<<"edit button not found";
        return;
    }


    rowIndex = btn->property("row").toInt();
    qInfo()<<"row index found next make the window";

    if (rowIndex < 0) {
        QMessageBox::warning(this, "Selection", "Please select a row to edit.");
        return;
    }
    // 2. Setup Dialog
    editDialog = new QDialog(this);
    editDialog->setWindowTitle(QString("Edit Row %1").arg(rowIndex + 1));
    editDialog->setMinimumSize(400, 300);
    editDialog->setWindowOpacity(0.8);
    // Use a dark background so text is visible
    editDialog->setStyleSheet("background-color: #2d2d2d; color: white; border: 1px solid purple; border-radius: 5px;");
    // 3. Get Current Data
    rowName   = recordsTabel->item(rowIndex, 0)->text();
    rowNumb   = recordsTabel->item(rowIndex, 1)->text();
    rowCateg = recordsTabel->item(rowIndex, 2)->text();
    rowDescr = recordsTabel->item(rowIndex, 3)->text();
    // 4. Create Layout
    layout = new QGridLayout(editDialog);
    layout->setSpacing(10);
    promptLabel = new QLabel("Edit the following details:", editDialog);
    promptLabel->setAlignment(Qt::AlignRight);
    promptLabel->setStyleSheet("background-color:#3f3f3f;font-size: 16px; font-weight: bold; color: gold; border: none;");
    lName = new QLabel("Name:", editDialog);
    eName = new QLineEdit(rowName, editDialog);
    lNumb = new QLabel("Number:", editDialog);
    eNumb = new QLineEdit(rowNumb, editDialog);
    lCateg = new QLabel("Category:", editDialog);
    eCateg = new QLineEdit(rowCateg, editDialog);
    lDescr = new QLabel("Description:", editDialog);
    eDescr = new QLineEdit(rowDescr, editDialog);

    // Apply Styles to LineEdits to match your app
    editStyle = "QLineEdit { background-color: "+btnBg+"; border: 1px solid #aa1293; padding: 5px; color: white; }";
    eName->setStyleSheet(editStyle);
    eNumb->setStyleSheet(editStyle);eNumb->setValidator(new QDoubleValidator(0.5,1000000.1,1,editDialog));
    eCateg->setStyleSheet(editStyle);
    eDescr->setStyleSheet(editStyle);
    lName->setStyleSheet("border: none;"); lNumb->setStyleSheet("border: none;");
    lCateg->setStyleSheet("border: none;"); lDescr->setStyleSheet("border: none;");

    saveBtn = new QPushButton("Save Changes", editDialog);
    saveBtn->setStyleSheet("background-color: "+accent+"; color: white; font-weight: bold; padding: 8px;");

    // 5. Add to Grid (Row, Col, RowSpan, ColSpan)
    layout->addWidget(promptLabel, 0, 0, 1, 2, Qt::AlignLeft);
    layout->addWidget(lName, 1, 0);   layout->addWidget(eName, 1, 1);
    layout->addWidget(lNumb, 2, 0);   layout->addWidget(eNumb, 2, 1);
    layout->addWidget(lCateg, 3, 0); layout->addWidget(eCateg, 3, 1);
    layout->addWidget(lDescr, 4, 0); layout->addWidget(eDescr, 4, 1);
    layout->addWidget(saveBtn, 5, 0, 1, 2);
    // 6. Connect Logic (Using Lambda to capture variables)
    connect(saveBtn, &QPushButton::clicked, [=,this]() {
        // Update the table
        recordsTabel->blockSignals(true);
        qInfo()<<"blocked signals";
        if(eName->text().isEmpty()|| eNumb->text().isEmpty() || eCateg->text().isEmpty() || eDescr->text().isEmpty()){
            qInfo()<<"Empty";
            QMessageBox::warning(this, "Error", "Fill Empty text Field(s)");
            return;
        }
        for(int i = 0; i<names.length();++i){
            if(eName->text() == names[i]){
                QMessageBox::warning(this, "Error", "Name Already Exists");
                return;
            }
        }
        recordsTabel->item(rowIndex, 0)->setText(eName->text());
        recordsTabel->item(rowIndex, 1)->setText(eNumb->text());
        recordsTabel->item(rowIndex, 2)->setText(eCateg->text());
        recordsTabel->item(rowIndex, 3)->setText(eDescr->text());
        saveTable();
        recordsTabel->blockSignals(false);
        // Close dialog
        editDialog->close();
    });

    saveCurrentState();
    editDialog->exec(); // Show as modal window
    recordsTabel->blockSignals(false);
    qInfo()<<"unblocked signals";
}
void Widget::showSettingDialog(){
    settingsDialog = new QDialog(this);
    settingsDialog->setWindowTitle("Settings");
    settingsDialog->setMinimumSize(QSize(500, 550));
    settingsDialog->resize(QSize(700, 600));
    settingsDialog->setAttribute(Qt::WA_DeleteOnClose);
    settingsDialog->setWindowFlag(Qt::FramelessWindowHint);
    QString stylessheest = R"(
      color:%6;
      QWidget#NavBoxWidget{
            color:%2;
            background-color:%1;
      }
      QPushButton#settings{
            font-size:%3;
            width:50px;
            height:25px;
            padding-left:15px;
            padding-right:15px;
      }QScrollArea{
            background: %1;
            border: none;
      }QPushButton{
            background-color:%2,color:%1;
      }QPushButton:disabled{
            border:none;

      }
      QPushButton::hover{background-color:%5;border:1px solid %1}
      QPushButton#exit::hover{background-color:red;}
      }QPushButton:pressed{background-color:%2;border:3px solid %4;}
      )";

    QVBoxLayout *settingsMaster = new QVBoxLayout(settingsDialog);
    settingsMaster->setContentsMargins(10, 10, 10, 10); // Give it some breathing room


    //[ Apearance ][Function]                     SETTINGS                                   [X]
    //                                    Apearance Settings                                                  =QLabel APearance settings
    //Theme:                                                                                                        =QLabel themeP
    //
    //      [SwitchTheme]
    //Choose Font Color:
    //      [Color]
    //Background Color:
    // [Color]
    //Choose Font:
    //     [Font]

    // --- Navigation Box ---
    QWidget *NavBoxWidget = new QWidget();
    NavBoxWidget->setObjectName("NavBoxWidget");
    QHBoxLayout *NavBox = new QHBoxLayout(NavBoxWidget);

    QPushButton *Apearance = new QPushButton("Appearance");
    QPushButton *function = new QPushButton("Function");
    QPushButton *exit = new QPushButton("X");

    // Object names for styling
    Apearance->resize(50,25);
    function->resize(50,25);
    exit->setObjectName("exit");exit->resize(25,25);

    NavBox->addWidget(Apearance);
    NavBox->addWidget(function);
    NavBox->addStretch(); // Pushes buttons to the left
    NavBox->addWidget(exit);

    // FIX 1: Add NavBox with 0 stretch so it stays small at the top
    settingsMaster->addWidget(NavBoxWidget, 0);

    // --- Stacked Widget with Scrolling ---
    QStackedWidget *tabsStack = new QStackedWidget();

    // Appearance Page (Scrollable)
    QScrollArea *scrollAppearance = new QScrollArea();
    scrollAppearance->setWidgetResizable(true);

    QWidget *ApearanceTweeksWidget = new QWidget();
    QGridLayout *ApearanceTweeks = new QGridLayout(ApearanceTweeksWidget);

    ApearanceSettings = new QLabel("Apearance Settings");
    themeCheck = new QCheckBox("Theme: ");
    switchTheme = new QPushButton("Switch Theme");
    switchTheme->setObjectName("settings");
    connect(themeCheck, &QCheckBox::toggled,[=,this]() {
        QString Labda = "themeCheck";
        lambdaFunctions(Labda);
    });
    connect(switchTheme,&QPushButton::clicked,[=,this](){
        QString swit = "switch";
        switchThemes(swit);
    });

    FGroundCheck = new QCheckBox("Font Color: ");
    FGroundEntry = new QPushButton("Choose");
    FGroundEntry->setObjectName("settings");

    BGroundCheck = new QCheckBox("BackGround Color: ");
    BGroundEntry = new QPushButton("Choose");
    BGroundEntry->setObjectName("settings");

    FontCheck = new QCheckBox("Change Font: ");
    FontEntry = new QPushButton("Change");
    FontEntry->setObjectName("settings");

    // Keeps buttons at the top
    scrollAppearance->setWidget(ApearanceTweeksWidget);

    // Function Page (Scrollable)
    QScrollArea *scrollFunction = new QScrollArea();
    scrollFunction->setWidgetResizable(true);
    scrollFunction->setStyleSheet("background: transparent; border: none;");

    QWidget *functionTweeksWidget = new QWidget();
    QVBoxLayout *functionTweeks = new QVBoxLayout(functionTweeksWidget);
    QPushButton *addPassWord = new QPushButton("+Add Password",functionTweeksWidget);
    QLabel *comments = new QLabel("Made By Awesome Effiong\n with the help of the qt6 group\n icons are from flaticon.com \n the hamburgerMenu from stats page is made by \nSee Icons the store icon freepik",functionTweeksWidget);

    // FIX 2: Add tabsStack with stretch factor 1 to fill ALL available space
    settingsMaster->addWidget(tabsStack, 1);

    ApearanceTweeks->addWidget(ApearanceSettings,0,2,1,1,Qt::AlignTop);

    ApearanceTweeks->addWidget(themeCheck,1,0,1,1,Qt::AlignTop);
    ApearanceTweeks->addWidget(switchTheme,2,0,1,1,Qt::AlignTop);

    ApearanceTweeks->addWidget(FGroundCheck,3,0,1,1,Qt::AlignTop);
    ApearanceTweeks->addWidget(FGroundEntry,4,0,1,1,Qt::AlignTop);

    ApearanceTweeks->addWidget(BGroundCheck,5,0,1,1,Qt::AlignTop);
    ApearanceTweeks->addWidget(BGroundEntry,6,0,1,1,Qt::AlignTop);

    ApearanceTweeks->addWidget(FontCheck,7,0,1,1,Qt::AlignTop);
    ApearanceTweeks->addWidget(FontEntry,8,0,1,1,Qt::AlignTop);

    tabsStack->addWidget(scrollAppearance);
    tabsStack->addWidget(scrollFunction);

    scrollFunction->setWidget(functionTweeksWidget);
    functionTweeks->addWidget(addPassWord);
    functionTweeks->addWidget(comments);
    functionTweeks->addStretch();

    // --- Logic & Styling ---
    // Connect Tab Switches
    connect(Apearance, &QPushButton::clicked, [=](){ tabsStack->setCurrentIndex(0); });
    connect(function, &QPushButton::clicked, [=](){ tabsStack->setCurrentIndex(1); });
    connect(exit, &QPushButton::clicked, this, &Widget::delSettingDialog);
    connect(FGroundEntry,&QPushButton::clicked,[=,this](){
        QString fg = "fg";
        showColorDialog(fg);
    });
    connect(BGroundEntry,&QPushButton::clicked,[=,this](){
        QString bg = "bg";
        showColorDialog(bg);
    });
    connect(FontEntry,&QPushButton::clicked,[=,this](){
        showFontDialog();
    });
    if (firstTime){//first time run everything should be checked
        themeCheck->setChecked(true);
        FGroundCheck->setChecked(true);
        BGroundCheck->setChecked(true);
        FontCheck->setChecked(true);
        firstTime = false;
    }// Update this line at the bottom of showSettingDialog
    //3 is font size 1 is background color 2 is btn background   t 5is accent 4 os jpver bg
    QString finalSheet = stylessheest.arg(bg,btnBg,fontSize,hoverBg,accent);
    settingsDialog->setStyleSheet(finalSheet);
settingsDialog->exec();}
void Widget::delSettingDialog(){settingsDialog->close();}
void Widget::showColorDialog(QString &value)
{
    QString thm = "custom";
    QString fg = "fg";
    QString bg = "bg";
    if (value=="fg"){
        QColor fontColor = QColorDialog::getColor(QColor::fromString(text),settingsDialog,"Font Color");
        if (fontColor.isValid()){
            if (fontColor.name() == bg | fontColor.name() == fg){
                return;
            }
            usertext = fontColor.name();
            switchThemes(thm);
        }return;
    }else if (value=="bg"){
        QColorDialog *backgroundColorDialog = new QColorDialog(settingsDialog);
        QColor backGroundColor = backgroundColorDialog->getColor(QColor::fromString(bg),settingsDialog,"Background Color");
        if (backGroundColor.isValid()){
            if (backGroundColor.name() == bg | backGroundColor.name() == fg){
                return;
            }
            userbg = backGroundColor.name();
            switchThemes(thm);
        }return;
    }
}
void Widget::showFontDialog()
{
    QString tim = "custom";

    bool ok;
    QFont font = QFontDialog::getFont(
        &ok, QFont("Helvetica [Cronyx]", 10), settingsDialog,"Choose App Font");
    if (ok){
        userfontName1 = font.family();
        userfontSize = font.pixelSize();
        switchThemes(tim);
        recordsTabel->setFont(font);
    }else {
        return;
    }

}//do this instead of using lambda
void Widget::lambdaFunctions(QString &value) {
    if (value == "stopTimer") {
        delTimer->stop();
    }else if (value == "themeCheck"){
        if (themeCheck->isChecked()){switchTheme->setDisabled(false);}
        else {switchTheme->setDisabled(true);}
    }
}
void Widget::saveCurrentState() {
    recordsTabel->blockSignals(true);
    TableState state;
    for(int i = 0; i < recordsTabel->rowCount(); ++i) {
        records rowData;
        rowData.Name = recordsTabel->item(i, 0)->text();
        rowData.Number = recordsTabel->item(i, 1)->text();
        rowData.Category = recordsTabel->item(i, 2)->text();
        rowData.Description = recordsTabel->item(i, 3)->text();
        rowData.Date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

        state.allRows.append(rowData);
    }
    if(!past.isEmpty()){
        if(state.allRows == past.last().allRows){
            return;
        }
    }
    past.append(state);
    recordsTabel->blockSignals(false);
}

void Widget::saveTable() {
    saveCurrentState();
    QString today = QDate::currentDate().toString("yyyy-MM-dd");
    QString todayHeader = "[" + today + "]{";

    // 1. Build today's data string
    QString todayContent = todayHeader + "\n";
    for(int i = 0; i < recordsTabel->rowCount(); ++i) {
        todayContent += "-new\n";
        todayContent += "N:\"" + (recordsTabel->item(i,0) ? recordsTabel->item(i,0)->text() : "") + "\"\n";
        todayContent += "I:\"" + (recordsTabel->item(i,1) ? recordsTabel->item(i,1)->text() : "0") + "\"\n";
        todayContent += "C:\"" + (recordsTabel->item(i,2) ? recordsTabel->item(i,2)->text() : "") + "\"\n";
        todayContent += "D:\"" + (recordsTabel->item(i,3) ? recordsTabel->item(i,3)->text() : "") + "\"\n";
        todayContent += "T:\"" + (recordsTabel->item(i,4) ? recordsTabel->item(i,4)->text() : "") + "\"\n";
    }
    todayContent += "}\n";

    // 2. Load the whole file to find where to swap
    QFile file(filePath);
    QString fullFile;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        fullFile = file.readAll();
        file.close();
    }

    // 3. The Swap Logic
    if (fullFile.contains(todayHeader)) {
        // Find the start and end of the old today block
        int start = fullFile.indexOf(todayHeader);
        int end = fullFile.indexOf("}", start) + 1;
        // Replace ONLY that section
        fullFile.replace(start, end - start, todayContent);
    } else {
        // If today doesn't exist, put it at the top
        fullFile.prepend(todayContent);
    }

    // 4. Write back
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        file.seek(0);
        file.resize(0);
        out << fullFile;
        file.close();
    }
    saveCurrentState();
}
void Widget::navigationPanelSetup()
{    // NavigationPanel

    NavPanel = new QFrame(this);
    NavPanel->setObjectName("NavigationalWidget");
    NavigationPanel = new QGridLayout(NavPanel);
    tabs = new QHBoxLayout();
    home = new QPushButton();
    store = new QPushButton();
    stats = new QPushButton();
    zion = new QLabel();
    zion->setObjectName("Zion");

    butns = new QHBoxLayout();
    minimize = new QPushButton();
    maximize = new QPushButton();
    exit = new QPushButton();

    // --- FIX 1: Corrected Paths again ---
    zion->setPixmap(QPixmap(":/images/Zions.png"));
    home->setIcon(QIcon(":/images/home.png"));
    store->setIcon(QIcon(":/images/store.png"));
    stats->setIcon(QIcon(":/images/stats.png"));

    store->setText("Store");
    stats->setText("Stats");
    zion->setText("Zion");
    home->setText("Home");
    minimize->setText("-");
    maximize->setText("[]");
    exit->setText("X");

    store->setIconSize(QSize(32, 32));
    home->setIconSize(QSize(27, 27));

    // Styling
    for(auto btns: {home,stats,store})btns->setObjectName("tabButtons");
    for(auto navBtns : {minimize,maximize,exit})navBtns->setStyleSheet("width:20;height:20");

    NavPanel->setMaximumHeight(50);
    NavigationPanel->setAlignment(Qt::AlignTop);

}

void Widget::mainUISetup()
{
    // Main UI Stack
    mainui = new QStackedWidget(this);
    mainui->setObjectName("tabstack");
    // Page 1: Home
    homepage = new QWidget();
    Main = new QVBoxLayout(homepage);
    welcome = new QLabel();
    status = new QLabel();
    add = new QPushButton();

    welcome->setText("Welcome to Zion records....");
    welcome->setObjectName("welcome");
    status->setText("You have not added any products yet. . ....");
    add->setText("Add");
    add->setStyleSheet(
        "font-family:consolas;font-weight:45px; padding:25%;border:white;border-width:5px;border-radius:25%;");
    add->setIcon(QIcon(":/images/add.png")); // Path fix
    add->setIconSize(QSize(32, 32));
    // Page 2: Store
    storepage = new QWidget(this);
    storeMenu = new QHBoxLayout(storepage);
    storesSidebar = new QVBoxLayout(storepage); // Removed 'this' to prevent layout warnings
    refresh = new QPushButton(this);
    prompt = new QLabel(this);
    namePrompt = new QLabel(this);
    namePrompt->setObjectName("prompt");
    name = new QLineEdit(this);
    numberPrompt = new QLabel(this);
    numberPrompt->setObjectName("prompt");
    number = new QLineEdit(this);
    categoriesPrompt = new QLabel(this);
    categoriesPrompt->setObjectName("prompt");
    categories = new QLineEdit(this);
    descriptionPrompt = new QLabel(this);
    descriptionPrompt->setObjectName("prompt");
    description = new QLineEdit();
    name->setMinimumWidth(200);
    Append = new QPushButton();
}

void Widget::signalSlotsSetup()
{
    connect(exit,       &QPushButton::clicked, this,&Widget::exitWindow);
    connect(maximize,   &QPushButton::clicked, this,&Widget::resizeWindow);
    connect(minimize,   &QPushButton::clicked, this,&Widget::minimizeWindow);
    connect(home,       &QPushButton::clicked, this,&Widget::homeTab);
    connect(store,      &QPushButton::clicked, this,&Widget::storeTab);
    connect(add,        &QPushButton::clicked, this,&Widget::storeTab);
    connect(stats,      &QPushButton::clicked, this,&Widget::statsTab);
    connect(Append,     &QPushButton::clicked, this,&Widget::addButton);
    connect(refresh,    &QPushButton::clicked, this,&Widget::rerfresher);
    connect(recordsTabel,    &QTableWidget::itemChanged, this,    &Widget::tableEdited);
    connect(searchName,      &QLineEdit::textEdited,     this,    &Widget::updateFilter);
    connect(searchNumber,    &QLineEdit::textEdited,     this,    &Widget::updateFilter);
    connect(searchCategory,  &QLineEdit::textEdited,     this,    &Widget::updateFilter);
    connect(searchDescription,&QLineEdit::textEdited,    this,    &Widget::updateFilter);

    connect(ctrlTabShortcut,     &QShortcut::activated, this, &Widget::switchTabs);
    connect(ctrlShiftTabShortcut,&QShortcut::activated, this, &Widget::switchTabs2);
    connect(undoShortcut,        &QShortcut::activated, this, &Widget::undoAction);
    connect(redoShortcut,        &QShortcut::activated, this, &Widget::redoAction);
    connect(windowShortcut1,       &QShortcut::activated, this, &Widget::windowAction1);
    connect(windowShortcut2,       &QShortcut::activated, this, &Widget::windowAction2);

    connect(clr,          &QPushButton::clicked, this, &Widget::format);
    connect(settings,     &QPushButton::clicked, this, &Widget::showSettingDialog);
    connect(enterShortcut, &QShortcut::activated, this, &Widget::enterAction);
    // Add these to signalSlotsSetup()
    connect(name,        &QLineEdit::returnPressed, this, &Widget::addButton);
    connect(number,      &QLineEdit::returnPressed, this, &Widget::addButton);
    connect(categories,  &QLineEdit::returnPressed, this, &Widget::addButton);
    connect(description, &QLineEdit::returnPressed, this, &Widget::addButton);
}

void Widget::redoAction()
{
    if (future.isEmpty()) return;
    TableState next = future.takeLast();
    //add to past so it can be reanimated(redone)
    past.append(next);

    //ADD to table and save Table () instead of adding to file

    parser(); // Reload table from the "reverted" file
    qInfo()<<"REDO";
}
void Widget::undoAction() {
    if (past.isEmpty()) return;
    TableState previous = past.takeLast();
    //add to future so it can be reanimated(redone)
    future.append(previous);
    QString content;
    QString fullFile;
    QString today = QDate::currentDate().toString("yyyy-MM-dd");
    QString todayHeader = "[" + today + "]{\n";
    QFile file(filePath);
    if(file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        fullFile = stream.readAll();
        for(records &row:previous.allRows){
            content += todayHeader+"-new\nN:\"" + row.Name+"\"\nI:\"" +row.Number+"\"\nC:\"" +row.Category + "\"\nD:\"" +row.Description +"\"\nT:\""+row.Date+"\"\n";
        }
        content.prepend(todayHeader);
        content .append( "}");
        int start = fullFile.indexOf("{");
        int end = fullFile.indexOf("}");
        if (start != -1 && end != -1) {
            fullFile.remove(0,end);
            fullFile.prepend(content);
        }
        stream<<fullFile;
        stream.flush();
        file.close();
    }
    parser(); // Reload table from the "reverted" file
    qInfo()<<"UNDO";
}

void Widget::enterAction() {
    // Option A: Direct approach - Get the specific widget that has focus right now
    QWidget* currentFocus = this->focusWidget();

    // Check if the focused widget is actually inside the homepage
    if (currentFocus && storepage->isAncestorOf(currentFocus)) {
        setActiveTab(store);
        addButton();
        // currentFocus is the widget you're looking for
    }
}
void Widget::windowAction1() {
    qInfo()<<"snap left";
    QRect screenGeom = this->screen()->availableGeometry();
    this->showNormal();
    this->setGeometry(screenGeom.x(), screenGeom.y(), screenGeom.width()/2, screenGeom.height());
}

void Widget::windowAction2() {
    // SNAP RIGHT
    qInfo()<<"snap RIGHT";
    QRect screenGeom = this->screen()->availableGeometry();
    int w = screenGeom.width() / 2;
    int h = screenGeom.height();

    // We start at the X-coordinate of the middle of the screen
    int startX = screenGeom.x() + w;

    this->showNormal();
    this->setGeometry(startX, screenGeom.y(), w, h);
}


void Widget::mousePressEvent(QMouseEvent *event) {
    // Only allow dragging from the NavigationPanel (your top bar)
    if (NavigationPanel->geometry().contains(event->pos())) {
        showNormal();
        m_isDragging = true;
        m_mousePosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }const int margin = 8;
    auto pos = event->position();

    // Determine which edge we are on
    Qt::Edges edges;
    if (pos.x() < margin) edges |= Qt::LeftEdge;
    if (pos.x() > width() - margin) edges |= Qt::RightEdge;
    if (pos.y() < margin) edges |= Qt::TopEdge;
    if (pos.y() > height() - margin) edges |= Qt::BottomEdge;

    if (edges != 0) {
        // If we are on an edge, let the OS handle the resize!
        windowHandle()->startSystemResize(edges);
    }
    else if (NavigationPanel->geometry().contains(event->pos())) {
        // Otherwise, handle dragging/moving
        m_isDragging = true;
        m_mousePosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }

}
void Widget::mouseMoveEvent(QMouseEvent *event) {
    if (m_isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_mousePosition);
        //8f t3 8nd9 s ca4483s 9t sd t sc4n tn s
        event->accept();
        showNormal();
    }
    const int margin = 8; // The "hit box" for the edge
    auto pos = event->position();

    bool left = pos.x() < margin;
    bool right = pos.x() > width() - margin;
    bool top = pos.y() < margin;
    bool bottom = pos.y() > height() - margin;

    if (left || right || top || bottom) {
        // Change cursor to show user they CAN resize
        if ((left && top) || (right && bottom)) setCursor(Qt::SizeFDiagCursor);
        else if ((left && bottom) || (right && top)) setCursor(Qt::SizeBDiagCursor);
        else if (left || right) setCursor(Qt::SizeHorCursor);
        else if (top || bottom) setCursor(Qt::SizeVerCursor);
    } else {
        unsetCursor();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event) {
    m_isDragging = false;
    // This allows the window to "stick" to its new position when you let go
    event->accept();
}
