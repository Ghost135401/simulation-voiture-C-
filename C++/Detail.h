#ifndef Detail_H
#define Detail_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include "Voiture.h"

class SpeedometerWidget : public QWidget {
    Q_OBJECT

public:
    SpeedometerWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void updateNeedle();

private:
    int m_angle;
    QTimer *m_timer;
};

class Detail : public QWidget {
    Q_OBJECT

public:
    Detail(const Voiture &voiture, QWidget *parent = nullptr);

private:
    Voiture m_voiture;
    SpeedometerWidget *m_speedometer;
};

#endif // Detail_H
