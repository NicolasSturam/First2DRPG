#include "Gobelin.h"

Gobelin::Gobelin(){
    pv = 0.0;
    pm = 0.0;
    name = "vide";
    sprite = NULL;
}

Gobelin::Gobelin(double pv, double pm, string name){
    this->pv = pv;
    this->pm = pm;
    this->name = name;
}

void Gobelin::getPv(){
    printf("Nombre de PV du gobelin : %f\n", pv);
}

void Gobelin::getPm(){
    printf("Nombre de PM du gobelin : %f\n", pm);
}

void Gobelin::getName(){
    printf("Nom du gobelin : %s\n", name.c_str());
}
