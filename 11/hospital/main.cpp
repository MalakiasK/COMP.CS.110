/* Sairaala
 *
 * Kuvaus:
 *
 * Ohjelma kuvaa sairaalan tietojärjestelmää. Sillä voidaan pitää kirjaa
 * tulleiden potilaiden hoitoajoista, potilaan hoitajista sekä potilaan
 * mahdollisista lääkityksistä. Tietokannassa voidaan myös pitää kirjaa
 * sairaalan työntekijöistä, sekä heidän potilaista. Tietokannasta saadaan
 * tietoja nykyisistä potilaista, kuin myös vanhoista/jo poistuneista
 * potilaista. Ohjelma on jaettu eri moduuleihin.
 *
 * Ohjelman kirjoittaja:
 *
 * Nimi: Malakias Kosonen
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * Ohjelma on kirjoitettu ja kommentoitu englanniksi, koska se on mielestäni
 * luontevaa. <Hospital.hh> otsikkotiedostossa oleva säiliö <patient_database_>
 * näyttää ensisilmäykseltä rumalta, ja niin se myös onkin. Se on kuitenkin
 * ohjelman kannalta toimiva, joten en jäänyt pohtimaan optimaalista
 * säiliöratkaisua liian pitkäksi aikaa. <hospital.cpp> tiedostossa olevissa
 * funktioissa <print_all_medicines> ja <print_all_patients> käytetään
 * lambda-funktiota. Tämän yksityiskohtaisesta toiminnasta en ole täysin varma
 * vielä, mutta se tekee tehtävänsä oikein.
 * */

#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
