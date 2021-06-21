class CoutTemp{
    private:
        double      distance;
        bool        sansRetard;
    public:
        CoutTemp();
        CoutTemp(const double& _distance, const bool& _sansRetard);
        double      obtenirDistance() const;
        bool        obtenirSansRetard() const;
        void        modifierDistance(double _distance);
        void        modifierSansRetard(bool _sansRetard);

};

CoutTemp::CoutTemp(const double& _distance, const bool& _sansRetard){
    distance = _distance;
    sansRetard = _sansRetard;
}

double CoutTemp::obtenirDistance() const{
    return distance;
}

bool CoutTemp::obtenirSansRetard() const{
    return sansRetard;
}

void CoutTemp::modifierDistance(double _distance){
    distance = _distance;
}

void CoutTemp::modifierSansRetard(bool _sansRetard){
    sansRetard = _sansRetard;
}