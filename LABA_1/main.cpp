#include <iostream>
#include <string>

using str = std::string;

class Country
{
public:
    Country()
    {
        nazvanie      = "neizvestno";
        stolica       = "neizvestno";
        dataOsnovania = "neizvestno";
        ploshad       = 0;
        naselenie     = 0;

        std::cerr << "konstruktor po umolchaniu" << std::endl;
    }

    Country(str nazv, str stol, str data, double plosh, long long nasel)
        : nazvanie(nazv),
          stolica(stol),
          dataOsnovania(data),
          ploshad(plosh),
          naselenie(nasel)
    {
        std::cerr << "konstruktor s parametrami" << std::endl;
    }

    Country(const Country& other)
        : nazvanie(other.nazvanie),
          stolica(other.stolica),
          dataOsnovania(other.dataOsnovania),
          ploshad(other.ploshad),
          naselenie(other.naselenie)
    {
        std::cerr << "konstruktor kopii" << std::endl;
    }

    ~Country()
    {
        std::cerr << "destruktor" << std::endl;
    }

    void set_stolica(str novaiaStolica)
    {
        if (novaiaStolica.empty())
        {
            throw str("Nazvanie stolici ne mozhet byt pustym");
        }

        if (novaiaStolica[0] < 'A' || novaiaStolica[0] > 'Z')
        {
            throw str("Stolica dolzhna nachinatsia s bolshoi bukvy");
        }

        for (int i = 1; i < novaiaStolica.length(); i++)
        {
            if (novaiaStolica[i] < 'a' || novaiaStolica[i] > 'z')
            {
                throw str("V nazvanii stolici tolko malenkie bukvy bez cifr i znakov");
            }
        }

        stolica = novaiaStolica;
        std::cerr << "Novaia stolica: " << stolica << std::endl;
    }

    str get_nazvanie() const { return nazvanie; }
    str get_stolica() const { return stolica; }
    str get_data_osnovania() const { return dataOsnovania; }
    double get_ploshad() const { return ploshad; }
    long long get_naselenie() const { return naselenie; }

    void dobavit_territoriu(double dobavka)
    {
        if (dobavka <= 0)
        {
            throw str("Dobavliaemaia ploshad dolzhna byt bolshe 0");
        }

        ploshad += dobavka;
        std::cout << "Novaia ploshad: " << ploshad << std::endl;
    }

    void uvelichit_naselenie()
    {
        long long dobavka;
        std::cout << "Vvedite skolko dobavit k naseleniu: ";
        std::cin >> dobavka;

        if (dobavka <= 0)
        {
            throw str("Uvelichenie dolzhno byt bolshe 0");
        }

        naselenie += dobavka;
        std::cout << "Tekuschee naselenie: " << naselenie << std::endl;
    }

    void pechat()
    {
        std::cout << "Informacia o strane:\n";
        std::cout << "Nazvanie: " << nazvanie << std::endl;
        std::cout << "Stolica: " << stolica << std::endl;
        std::cout << "Data osnovania: " << dataOsnovania << std::endl;
        std::cout << "Ploshad: " << ploshad << std::endl;
        std::cout << "Naselenie: " << naselenie << std::endl;
    }

private:
    str       nazvanie;
    str       stolica;
    str       dataOsnovania;
    double    ploshad;
    long long naselenie;
};

int main()
{
    Country atlantida("Atlantida", "Poseidon", "10000 let do n.e.", 98765.4, 123456);
    Country atlantidaKopia(atlantida);
    Country pustayaStrana;

    pustayaStrana.pechat();

    int vibor = 0;

    do
    {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Pokazat nazvanie\n";
        std::cout << "2. Pokazat stolicu\n";
        std::cout << "3. Pokazat datu osnovania\n";
        std::cout << "4. Pokazat ploshad\n";
        std::cout << "5. Pokazat naselenie\n";
        std::cout << "6. Izmenit stolicu\n";
        std::cout << "7. Dobavit territoriu\n";
        std::cout << "8. Uvelichit naselenie\n";
        std::cout << "9. Pokazat vse\n        ";
        std::cout << "0. Vyhod\n";
        std::cout << "Vash vibor: ";

        std::cin >> vibor;

        str novaiaStolica;
        double dobavka;

        try
        {
            switch (vibor)
            {
            case 1:
                std::cout << atlantida.get_nazvanie() << std::endl;
                break;
            case 2:
                std::cout << atlantida.get_stolica() << std::endl;
                break;
            case 3:
                std::cout << atlantida.get_data_osnovania() << std::endl;
                break;
            case 4:
                std::cout << atlantida.get_ploshad() << std::endl;
                break;
            case 5:
                std::cout << atlantida.get_naselenie() << std::endl;
                break;
            case 6:
                std::cout << "Vvedite novuyu stolicu: ";
                std::cin >> novaiaStolica;
                atlantida.set_stolica(novaiaStolica);
                break;
            case 7:
                std::cout << "Vvedite dobavlyaemuyu ploshad: ";
                std::cin >> dobavka;
                atlantida.dobavit_territoriu(dobavka);
                break;
            case 8:
                atlantida.uvelichit_naselenie();
                break;
            case 9:
                atlantida.pechat();
                break;
            case 0:
                std::cout << "Vyhod iz programmy\n";
                break;
            default:
                std::cout << "Nevernyi vibor\n";
            }
        }
        catch (str oshibka)
        {
            std::cerr << "Oshibka: " << oshibka << std::endl;
        }

    } while (vibor != 0);

    return 0;
}