#include <QtMath>
#include "Detail.h"

SpeedometerWidget::SpeedometerWidget(QWidget *parent)
    : QWidget(parent), m_angle(0) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SpeedometerWidget::updateNeedle);
    m_timer->start(50);  // Mise à jour toutes les 50 ms
}

void SpeedometerWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    // Dessiner le cadran (cercle de vitesse)
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(50, 50, 200, 200);

    // Dessiner l'aiguille
    painter.setPen(QPen(Qt::red, 3));
    int needleLength = 90;
    int x = 150 + needleLength * qCos(qDegreesToRadians(static_cast<float>(m_angle)));
    int y = 150 - needleLength * qSin(qDegreesToRadians(static_cast<float>(m_angle)));

    painter.drawLine(150, 150, x, y);

    // Dessiner le réservoir d'essence (petit carré)
    int fuelSize = 100 * m_fuelLevel / 100;  // Taille du réservoir en fonction du niveau de carburant
    QRect fuelRect(250, 150, fuelSize, fuelSize);  // Position et taille du carré
    painter.setBrush(QBrush(Qt::green));  // Couleur du réservoir
    painter.drawRect(fuelRect);
}

void SpeedometerWidget::updateNeedle() {
    // Animation de l'aiguille (déplacer l'angle de 0 à 120 km/h)
    m_angle += 0.5;
    if (m_angle > 120) {
        m_angle = 0;  // Réinitialiser l'angle à 0 pour recommencer
    }
    update();  // Redessiner le widget
}

Detail::Detail(const Voiture &voiture, QWidget *parent)
    : QWidget(parent), m_voiture(voiture), m_fuelLevel(100) {  // Niveau d'essence par défaut à 100%
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Affichage du nom de la voiture
    QLabel *nameLabel = new QLabel("Nom de la voiture: " + QString::fromStdString(m_voiture.getNom()), this);
    layout->addWidget(nameLabel);

    // Affichage de l'image du réservoir d'essence (optionnel)
    QLabel *fuelImage = new QLabel(this);
    fuelImage->setPixmap(QPixmap(":/images/fuel_tank.png").scaled(100, 100));
    layout->addWidget(fuelImage);

    // Ajout du tableau de bord (cadran de vitesse et aiguille)
    m_speedometer = new SpeedometerWidget(this);
    layout->addWidget(m_speedometer);

    setLayout(layout);
    setWindowTitle("Détails de la Voiture");
    resize(400, 400);
}

void Detail::setFuelLevel(float level) {
    m_fuelLevel = qBound(0.0f, level, 100.0f);  // Assure-toi que le niveau est entre 0 et 100
    m_speedometer->update();  // Rafraîchir l'affichage du speedometer
}
