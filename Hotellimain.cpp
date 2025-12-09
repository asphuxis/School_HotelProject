// Jaakko Hautala, yritän ainaki 3

#include <vector>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
using namespace std;

// Numerogeneraattori
int random_generator(int min, int max) { 
    random_device seeder;
    mt19937 engine(seeder());
    uniform_int_distribution dist(min, max);
    return dist(engine);
}

// true false generaattori
bool truefalse_generator(int min, int max) { 
    random_device seeder;
    mt19937 engine(seeder());
    uniform_int_distribution dist(min, max);
    return dist(engine);
}

// Huonerakenne
struct room{ 
    int roomnum;
    bool roomtype;
    bool reserved;
    int resnum;
    string user;
};

// Kyselyjen virheentarkistusfunktio
bool check_error_bool(bool user_input){ 
    while (!(cin >> user_input))
    {
        cout << "Something went wrong, please try again : ";
        cin. clear();
        cin.ignore(1000, '\n');
    }
    return(user_input);
}

// Nimen kysely ja tarkistusfunktio
string check_reservation_name(string reservation_name){ 
    bool input;

    do
    {
        cout << "What name will this reservation be made with? : ";
        cin >> reservation_name;
        cout << "Is " << reservation_name << " correct?" << endl;
        cout << "Type [0] for no and [1] for yes : ";
        input = check_error_bool(input);

        if (input == 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        
    } while (input == 0);

    return(reservation_name);
}

// Huoneen hintalaskin, ottaa ensin huoneen hinnan suhteessa kokoon ja määrittää sille alennusprosentin 20%, 10% tai 0%
int room_cost_generator(int cost){ 
    if (cost == 0){ // Määrittää huoneen perusteella lähtöhinnan
        cost = 100;
    } else if (cost == 1){
        cost = 150;
    }

    float discount_multiplier = random_generator(8,10)/10.0; // Luo alennusprosenttikertoimen
    int final_cost = cost*discount_multiplier; // Laskee lopullisen hinnan
    return(final_cost);
}


int main(){ // Ohjelman runko

    const int user_resnum = random_generator(10000,99999); // Määrittää satunnaisen varausnumeron
    vector<room> rooms; // huoneille vektori
    string reservation_name; // varaajan nimi
    bool user_input; // kyselymuuttuja

    cout << "Welcome to Hotel C++! Would you like to book a room?" << endl;
    cout << "Type [0] for no and [1] for yes : ";

    user_input = check_error_bool(user_input);

    // Sammuttaa ohjelman jos käyttäjä ei halua varata huoneita ja luo huoneet mikäli haluaa.
    if (user_input == 0 ) 
    {
        system("cls");
        cout << "Goodbye" << endl;
        return(0);
    } else if (user_input == 1)
    {
        int rooms_amount = 0;

        do // Lue huoneita 40-300, kuitenkin sellaisen määrän, että se on parillinen määrä
        {
            rooms_amount = random_generator(40,300);
        } while (!(rooms_amount % 2 == 0));
        
        int single_rooms = rooms_amount/2; // Määrittää yksiöiden määrän puoleen kaikkien huoneiden määrästä

        for (int i = 1; i < single_rooms; i++)
        {
            room a {i, 0, truefalse_generator(0,1), 0, "Unknown"};
            rooms.push_back(a);
        }

        int double_rooms = rooms_amount/2; // Määrittää kaksioiden määrän toiseen puoleen kaikkien huoneiden määrästä

        for (int i = rooms_amount/2; i < rooms_amount; i++)
        {
            room a {i, 1, truefalse_generator(0,1), 0, "Unknown"};
            rooms.push_back(a);
        }
    }

    // Varaus alkaa
    cout << "What kind of room would you like to book?" << endl;
    cout << "Type [0] for singles and [1] for doubles : ";

    user_input = check_error_bool(user_input); // Tarkistaa käyttäjän syötteen ja määrittää sen muuttujaan
    bool user_roomtype = user_input; // Määrittää vastauksen huonetyypiksi

    // Laskee huoneen hinnan pohjautuen huonevalintaan
    int room_cost = room_cost_generator(user_input); 

    cout << "The cost per night for you is " << room_cost << endl;
    
    // Kysyy varaukselle nimen
    reservation_name = check_reservation_name(reservation_name); 

    int user_roomnum;

    // Käy vektorit läpi ja etsii huoneen joka täyttää käyttäjän kriteerit, jonka jälkeen määrittää vektoriin käyttäjän syöttämät arvot
    for (int i = 0; i < rooms.size(); i++) 
    {
        if (rooms.at(i).roomtype == user_roomtype && !rooms.at(i).reserved)
        {
            user_roomnum = (rooms.at(i).roomnum); // Noutaa huonenumeron ja määrittää sen muuttujaan
            rooms.at(i).resnum = user_resnum; // Määrittää varausnumeron 
            rooms.at(i).user = reservation_name; // Määrittää varausnimen
            rooms.at(i).reserved = true; // Määrittää huoneen tilan varatuksi
            break;
        }
    }

    cout << "Thank you for your reservation." << endl;
    cout << "Your reservation number is " << user_resnum << " and your room number is " << user_roomnum << endl;
    system("pause");

    return(0);
}