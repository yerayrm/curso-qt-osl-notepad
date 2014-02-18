#include "notepadwindow.h"

// constructor
NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    txtEditor_ = new QPlainTextEdit(this);
    setCentralWidget(txtEditor_);

    // inicializamos los menus
    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);                          // el & sirve para abrir un acceso directo
    mainMenu_ -> addMenu(mnuArchivo_);

    setMenuBar(mainMenu_);

    actArchivoAbrir_ = new QAction(QIcon("open"), tr("&Abrir"), this);                         // instancio una accion para el menu archivo
    actArchivoAbrir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));        // acceso directo
    mnuArchivo_->addAction(actArchivoAbrir_);                                   // asigno la accion al menu

    actArchivoGuardar_ = new QAction(QIcon("save"), tr("&Guardar"), this);                     // instancio una accion para el menu archivo
    actArchivoGuardar_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));      // acceso directo
    mnuArchivo_->addAction(actArchivoGuardar_);                                 // asigno la accion al menu

    actArchivoCerrar_ = new QAction(tr("&Cerrar"), this);                     // instancio una accion para el menu archivo
    actArchivoCerrar_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));      // acceso directo
    mnuArchivo_->addAction(actArchivoCerrar_);                                 // asigno la accion al menu


    mnuEditar_ = new QMenu(tr("&Editar"));
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarDeshacer_ = new QAction(QIcon("undo"), tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(QIcon("redo"), tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRehacer_);

    mnuFormato_ = new QMenu(tr("&Formato"));
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"));
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcercade_);

    // toolbar
    QToolBar *toolbar = addToolBar("Principal");
    toolbar->addAction(actArchivoAbrir_);
    toolbar->addAction(actArchivoGuardar_);
    toolbar->addAction(actEditarDeshacer_);
    toolbar->addAction(actEditarRehacer_);


    // conectar las acciones a los slots
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(alAbrir()) );     //triggered es una señar del objeto QAction cuando hacemos click en la opcion
    connect(actArchivoGuardar_, SIGNAL(triggered()), this, SLOT(alGuardar()) );
    connect(actArchivoCerrar_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
    connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));
    connect(actAyudaAcercade_, SIGNAL(triggered()), this, SLOT(alAcercade()));
}

// destructor
NotepadWindow::~NotepadWindow()
{

}

// metodo abrir
void NotepadWindow::alAbrir()
{
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));

    if (nombreArchivo != "") {
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            txtEditor_->setPlainText(archivo.readAll());
            archivo.close();
        }
    }

}

// metodo guardar
void NotepadWindow::alGuardar()
{
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));

    if (nombreArchivo != "") {
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            archivo.write(txtEditor_->toPlainText().toUtf8());
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}

void NotepadWindow::alAcercade()
{
    QMessageBox::about(this, "Acerca de...", "Sublime Yeray");
}


