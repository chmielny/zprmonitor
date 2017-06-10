/**
 * @file
 *
 * \class DaemonObserver
 * Klasa DaemonObserver jest klasa bazowa dla wszystkich obserwatorow (overrunn, underrun, inrange, averageoverrun, averageunderrun).
 * Metoda operator() kazdej z klas dziedziczacych wywoluje metode update(). W metodzie update sprawdzany jest warunek obserwatora
 * np przekroczenie parametru i ew. wywolanie funkcji spod wskaznika userFunctionPtr_ - czyli wskaznika zarejestrowanego z zewnatrz.
 * Operator == jest konieczny dla metody disconnect() z boost signals2. Cala klasa jest traktowana jako funktor podlaczany do daemona
 * np badajacego CPU. Jezeli chcemy odlaczyc obserwatora, a do daemona jest podlaczonych kilku obserwatorow to musimy wiedziec jak porownac
 * usuwany slot ze slotami listy (czyli obiektami DaemonObserver). Po to jest wlasnie operator ==.
 */
#ifndef DAEMONOBSERVER_HPP_
#define DAEMONOBSERVER_HPP_
#include <functional>

class DaemonObserver {
protected:
	std::function<void(void)> userFunctionPtr_;
public:
	DaemonObserver( std::function<void(void)> );
	virtual ~DaemonObserver( );
	virtual void update(int) {} ;
	virtual void operator()(int) {} ;
    bool operator ==( const DaemonObserver& ) const;        //potrzebny do boost signals2 disconnect
};


#endif //DAEMONOBSERVER_HPP_
