#pragma once

#include "stdafx.h"
#include "constantes.h"

template <class T> class Cooldown {
	std::shared_ptr<T> object;
	int recovery;
	int cooldown;
	bool isStarted;

public:
	Cooldown(int recovery, T * o = nullptr);
	void start();
	void update();
	bool isDone();
	void reset();
	T* getObject();
	void setObject(T* o);
};

template<class T>
inline Cooldown<T>::Cooldown(int recovery, T * o) :
	object(o), recovery(recovery), cooldown(0), isStarted(false)
{}

template<class T>
inline void Cooldown<T>::start() { isStarted = true; cooldown = 0; }

template<class T>
inline void Cooldown<T>::update() {
	if (cooldown == recovery) {
		cooldown = 0;
		isStarted = false;
	}
	if (isStarted)
		cooldown = std::min(cooldown + 1, recovery);
}

template<class T>
inline bool Cooldown<T>::isDone() {
	return cooldown == 0 && !isStarted;
}

template<class T>
inline void Cooldown<T>::reset() {
	cooldown = 0;
	isStarted = false;
}

template<class T>
inline T * Cooldown<T>::getObject() {
	return object.get();
}

template<class T>
inline void Cooldown<T>::setObject(T * o) {
	object.reset(o);
}
