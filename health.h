#ifndef HEALTH_H
#define HEALTH_H

class Health {

public:
  Health(int initialHealth);

  void decrease(int damage);
  int getHealth();

private:
  int health;
};

#endif // HEALTH_H
