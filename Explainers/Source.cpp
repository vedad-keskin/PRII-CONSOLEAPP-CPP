#include <iostream>
using namespace std;

const char* crt = "\n-------------------------------------------\n";

template<class T1, class T2>
class Rjecnik {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Rjecnik(bool omoguciDupliranje = true) {
		_omoguciDupliranje = omoguciDupliranje;
		_trenutno = 0;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		
	}

	Rjecnik(const Rjecnik& obj)
	{
		_omoguciDupliranje = obj._omoguciDupliranje;
		_trenutno = obj._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}

	Rjecnik& operator=(const Rjecnik& obj)
	{
		if (this != &obj)
		{
			delete[] _elementi1;
			delete[] _elementi2;

			_omoguciDupliranje = obj._omoguciDupliranje;
			_trenutno = obj._trenutno;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (int i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}
		}
		return *this;
	}

	~Rjecnik() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}

	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }

	void AddElement(T1 el1, T2 el2)
	{
		if (!_omoguciDupliranje) {
			for (int i = 0; i < _trenutno; i++) {
				//      Zadovoljstvo == Zadovljtsvo
				if (_elementi1[i] == el1 && _elementi2[i] == el2) {
					throw exception("Dupliranje nije dozvoljeno");
				}
			}
		}

		T1* temp1 = _elementi1;
		T2* temp2 = _elementi2;

		_elementi1 = new T1[_trenutno + 1];
		_elementi2 = new T2[_trenutno + 1];

		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = temp1[i];
			_elementi2[i] = temp2[i];
		}

		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		_trenutno++;
	}

	//                   2
	void RemoveAt(int pozicija) {

		for (int i = pozicija; i < _trenutno-1; i++)
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutno--;


	}

	Rjecnik<int, int> RemoveAt2(int pozicija) {

		Rjecnik<int, int> novakolekcija;


		for (int i = pozicija; i < _trenutno - 1; i++)
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutno--;

		for (int i = 0; i < _trenutno; i++)
		{
			novakolekcija.AddElement(_elementi1[i], _elementi2[i]);
		}

		return novakolekcija;

	}


	Rjecnik<int, int> RemoveAt3(int pozicija) {

		Rjecnik<int, int> novakolekcija;

		novakolekcija.AddElement(_elementi1[pozicija], _elementi2[pozicija]); //  0 0

		for (int i = pozicija; i < _trenutno - 1; i++)
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutno--;

		return novakolekcija;

	}

	void InsertAt(int pozicija, T1 el1, T2 el2) {

		T1* temp1 = _elementi1;
		T2* temp2 = _elementi2;

		_elementi1 = new T1[_trenutno + 1];
		_elementi2 = new T2[_trenutno + 1];

		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = temp1[i];
			_elementi2[i] = temp2[i];
		}

		for (int i = _trenutno; i > pozicija; i--)
		{
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}
		_elementi1[pozicija] = el1;
		_elementi2[pozicija] = el2;
		_trenutno++;


	}


	Rjecnik<int, int> operator() (int pocetak, int kraj) {
		Rjecnik<int, int> novakolekcija;
		for (int i = pocetak; i <= kraj; i++) {
			novakolekcija.AddElement(_elementi1[i], _elementi2[i]);
		}
		return novakolekcija;
	}

	T2& operator [] (T1 el1) {

		for (int i = 0; i < _trenutno; i++)
		{
			if (el1 == _elementi1[i]) {
				return _elementi2[i];
			}
		}

	}









	friend ostream& operator<< (ostream& COUT, const Rjecnik& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};


void main() {



	const int rjecnikTestSize = 9;

	cout << "---------------1. ADD ELEMENT-----------------" <<endl<< endl;


	Rjecnik<int, int> rjecnik1(false);
	for (int i = 0; i < rjecnikTestSize - 1; i++)
		rjecnik1.AddElement(i, i);//dodaje vrijednosti u rjecnik

	cout << rjecnik1 << crt;


	cout << "---------------2. REMOVE AT ORIGINAL (2)-----------------" << endl << endl;

	rjecnik1.RemoveAt(2);
	// 0 0 
	// 1 1
	// 3 3
	// 4 4

	cout << rjecnik1 << crt;

	cout << "---------------3. REMOVE AT KADA IMAMO NOVAKOLEKCIJA -- (1)-----------------" << endl << endl;

	// Hocemo novukolkciju i da i ona i stara izgube poziciju 1
	// 0 0
	// 3 3
	// 4 4

	// 0 0
	// 3 3
	// 4 4
	Rjecnik<int, int> rjecnik2 = rjecnik1.RemoveAt2(1);

	cout << rjecnik1 << crt;
	cout << rjecnik2 << crt;

	cout << "---------------4. REMOVE AT KADA IMAMO NOVAKOLEKCIJA -- (0)-----------------" << endl << endl;

	// Hocemo da jedna kolekcija ima samo 0 0 a da druga to isto samo izgubi
        // 0 0

	// 3 3
	// 4 4
	//...
	Rjecnik<int, int> rjecnik3 = rjecnik1.RemoveAt3(0);

	cout << rjecnik1 << crt;
	cout << rjecnik3 << crt;

	cout << "---------------5. INSERT AT ORIGINAL (0,9,9)-----------------" << endl << endl;

	rjecnik1.InsertAt(0,9,9);
	// 9 9 
	// 3 3 
	// 4 4
	//...

	cout << rjecnik1 << crt;


	cout << "---------------6. OPERATOR  ( ) NOVAKOLEKCIJA (2,5) -----------------" << endl << endl;


	Rjecnik<int, int> rjecnik4 = rjecnik1(2,5);

	// Novakolekcija ce imati elemente od 2 do 5
	// 4 4
	// 5 5
	// 6 6
	// 7 7 

	cout << rjecnik4 << crt;

	
	cout << "---------------7. OPERATOR [ ] NA OSNOVU T1 mijenja T2 -----------------" << endl << endl;


	rjecnik1[9] = 2;
	// 9 2
	// 3 3 
	// 4 4

	cout << rjecnik1 << crt;



	cin.get();
	system("pause>0");
}


#include<iostream>
using namespace std;


const char* crt = "\n-------------------------------------------\n";



template<class T1, class T2, int max = 10>
class Rijecnik {
    T1* _elementi1[max];
    T2* _elementi2[max];
    int* _trenutno;
    bool _omoguciDupliranje;

public:
    Rijecnik(bool omoguciDupliranje = true) {
        _trenutno = new int(0);
        _omoguciDupliranje = omoguciDupliranje;
    }

    Rijecnik(const Rijecnik& obj) {
        _trenutno = new int(*obj._trenutno);
        _omoguciDupliranje = obj._omoguciDupliranje;
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = new T1(*obj._elementi1[i]);
            _elementi2[i] = new T2(*obj._elementi2[i]);
        }
    }

    Rijecnik& operator=(const Rijecnik& obj) {
        if (this != &obj) {

            delete _trenutno; _trenutno = nullptr;
            for (size_t i = 0; i < *_trenutno; i++)
            {
                delete[]_elementi1[i]; _elementi1 = nullptr;
                delete[]_elementi2[i]; _elementi2 = nullptr;
            }

            _trenutno = new int(*obj._trenutno);
            _omoguciDupliranje = obj._omoguciDupliranje;
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = new T1(*obj._elementi1[i]);
                _elementi2[i] = new T2(*obj._elementi2[i]);
            }
        }
        return *this;
    }

    void AddElement(T1 el1, T2 el2) {
        if (_omoguciDupliranje == false) {
            for (size_t i = 0; i < *_trenutno; i++) {
                if (*_elementi1[i] == el1 && *_elementi2[i] == el2)
                    throw exception("Nema dupliranja!");
            }
        }
        if (*_trenutno == max)
            throw exception("Rijecnik je popunjen");

        _elementi1[*_trenutno] = new T1(el1);
        _elementi2[*_trenutno] = new T2(el2);

        (*_trenutno)++;
    }



    void RemoveAt(int pozicija){

        for (int i = pozicija; i < *_trenutno-1; i++)
        {
            _elementi1[i] = new T1(*_elementi1[i + 1]);
            _elementi2[i] = new T2(*_elementi2[i + 1]);
        }
        (*_trenutno)--;


    }







    Rijecnik<T1, T2, max> RemoveAt2(int lokacija) {
        Rijecnik<T1, T2, max> novakolekcija;

        for (int i = lokacija; i < *_trenutno - 1; i++)
        {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }
        (*_trenutno)--;

        for (int i = 0; i < *_trenutno; i++)
        {
            novakolekcija.AddElement(*_elementi1[i], *_elementi2[i]);
        }



        return novakolekcija;

    }

    Rijecnik<T1, T2, max> RemoveAt3(int lokacija) {
        Rijecnik<T1, T2, max> novakolekcija;

        novakolekcija.AddElement(*_elementi1[lokacija], *_elementi2[lokacija]);

        for (int i = lokacija; i < *_trenutno - 1; i++)
        {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }
        (*_trenutno)--;

  



        return novakolekcija;

    }


    void InsertAt(int pozicija, T1 el1, T2 el2) {

  

        for (int i = *_trenutno; i > pozicija; i--)
        {
            _elementi1[i] = new T1(*_elementi1[i - 1]);
            _elementi2[i] = new T2(*_elementi2[i - 1]);
        }
        _elementi1[pozicija] = new T1(el1);
        _elementi2[pozicija] = new T2(el2);
        (*_trenutno)++;


    }

    Rijecnik<int, int,max> operator() (int pocetak, int kraj) {
        Rijecnik<int, int,max> novakolekcija;
        for (int i = pocetak; i <= kraj; i++) {
            novakolekcija.AddElement(*_elementi1[i], *_elementi2[i]);
        }
        return novakolekcija;
    }

    T2& operator [] (T1 el1) {

        for (int i = 0; i < *_trenutno; i++)
        {
            if (el1 == *_elementi1[i]) {
                return *_elementi2[i];
            }
        }

    }




    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Rijecnik& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    ~Rijecnik() {
        for (size_t i = 0; i < *_trenutno; i++)
        {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
        delete _trenutno; _trenutno = nullptr;
    }


};






void main() {

 



    const int rijecnikTestSize = 9;
    Rijecnik<int, int, rijecnikTestSize> rijecnik1(false);



    cout << "---------------1. ADD ELEMENT-----------------" << endl << endl;


    for (int i = 0; i < rijecnikTestSize - 1; i++)
        rijecnik1.AddElement(i, i);//dodaje vrijednosti u rijecnik


    cout << rijecnik1 << crt;


    cout << "---------------2. REMOVE AT ORIGINAL (2)-----------------" << endl << endl;

    rijecnik1.RemoveAt(2);
    // 0 0 
    // 1 1
    // 3 3
    // 4 4

    cout << rijecnik1 << crt;

    cout << "---------------3. REMOVE AT KADA IMAMO NOVAKOLEKCIJA -- (1)-----------------" << endl << endl;

    // Hocemo novukolkciju i da i ona i stara izgube poziciju 1
    // 0 0
    // 3 3
    // 4 4

    // 0 0
    // 3 3
    // 4 4
    Rijecnik<int, int,rijecnikTestSize> rijecnik2 = rijecnik1.RemoveAt2(1);

    cout << rijecnik1 << crt;
    cout << rijecnik2 << crt;

    cout << "---------------4. REMOVE AT KADA IMAMO NOVAKOLEKCIJA -- (0)-----------------" << endl << endl;

    // Hocemo da jedna kolekcija ima samo 0 0 a da druga to isto samo izgubi
    // 0 0

    // 3 3
    // 4 4
    //...
    Rijecnik<int, int, rijecnikTestSize> rijecnik3 = rijecnik1.RemoveAt3(0);

    cout << rijecnik1 << crt;
    cout << rijecnik3 << crt;

    cout << "---------------5. INSERT AT ORIGINAL (0,9,9)-----------------" << endl << endl;

    rijecnik1.InsertAt(0, 9, 9);
    // 9 9 
    // 3 3 
    // 4 4
    //...

    cout << rijecnik1 << crt;


    cout << "---------------6. OPERATOR  ( ) NOVAKOLEKCIJA (2,5) -----------------" << endl << endl;


    Rijecnik<int, int,rijecnikTestSize> rijecnik4 = rijecnik1(2, 5);

    // Novakolekcija ce imati elemente od 2 do 5
    // 4 4
    // 5 5
    // 6 6
    // 7 7 

    cout << rijecnik4 << crt;

    cout << "---------------7. OPERATOR [ ] NA OSNOVU T1 mijenja T2 -----------------" << endl << endl;


    rijecnik1[9] = 2;
    // 9 2
    // 3 3 
    // 4 4

    cout << rijecnik1 << crt;




    cin.get();
    system("pause>0");
}