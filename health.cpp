#include "health.h"

/**
 * @brief Health::Health
 * @param initialHealth Initial health level
 * @param parent
 */
Health::Health(int initialHealth) {

  // initialize health to
  health = initialHealth;
  // display th health
//  setPlainText(QString("Health: ") + QString::number(health));
//  setDefaultTextColor(Qt::red);
//  setFont(QFont("times", 16));
}


/**
 * @brief Health::decrease
 * @param damage Damage inflicted (how much health decreases)
 */
void Health::decrease(int damage) {
  health -= damage;
}

int Health::getHealth() {
  return health;
}
