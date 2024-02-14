#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include<vector>
#include<set>
#include <map>
using namespace std;
class IFile {
	virtual void saveToFile1(fstream& file) = 0;
	virtual void restoreFromFile1(fstream& file) = 0;
};
class StocMateriePrima:IFile
{
	string denumireMateriePrima = "Anonima";
	string unitateMasura = "anonima";
	float cantitateStoc = 0;
	static string furnizorMateriePrima;
public:
	StocMateriePrima() {}
	
	StocMateriePrima(string denumireMateriePrima, string unitateMasura, float cantitateStoc) {

		this->denumireMateriePrima=denumireMateriePrima;
		this->unitateMasura = unitateMasura;
		this->cantitateStoc = cantitateStoc;
	}
	StocMateriePrima(const StocMateriePrima& s)
	{
		this->denumireMateriePrima = s.denumireMateriePrima;
		this->unitateMasura = s.unitateMasura;
		this->cantitateStoc = s.cantitateStoc;
	}
	StocMateriePrima& operator=(const StocMateriePrima& s)
	{
		if (this != &s)
		{

			this->denumireMateriePrima = s.denumireMateriePrima;
			this->unitateMasura = s.unitateMasura;
			this->cantitateStoc = s.cantitateStoc;
		}
		return *this;
	}
	void setDenumireMateriePrima(string denumireMateriePrima)
	{
		if (denumireMateriePrima.length()>1) {
			this->denumireMateriePrima = denumireMateriePrima;
		}
	}
	string getDenumireMateriePrima()
	{
		return this->denumireMateriePrima;
	}
	void setUnitateMasura(string unitateMasura)
	{
		if (unitateMasura.length() > 0)
			this->unitateMasura = unitateMasura;
	}
	string getUnitateMasura()
	{
		return this->unitateMasura;
	}
	void setCantitateStoc(float cantitateStoc)
	{
		if (cantitateStoc >= 0)
			this->cantitateStoc = cantitateStoc;
	}
	float& getCantitateStoc()
	{
		return this->cantitateStoc;
	}
	static void setFurnizorMateriePrima(string furnizor)
	{
		if (furnizor.length() > 2)
			StocMateriePrima::furnizorMateriePrima = furnizor;
	}
	static string getFurnizorMateriePrima()
	{
		return StocMateriePrima::furnizorMateriePrima;
	}
	~StocMateriePrima() = default;
	friend ostream& operator<<(ostream& out, const StocMateriePrima& s)
	{
		out << "\n*********MATERIE PRIMA************";
		out << "\nDenumire materie prima: " << s.denumireMateriePrima;
		out << "\nCantitate disponibila pe stoc: " << s.cantitateStoc << " " << s.unitateMasura;
		out << "\nFurnizor: " << StocMateriePrima::furnizorMateriePrima;
		out << "\n*************************";
		return out;
	}
	friend istream& operator>>(istream& in, StocMateriePrima& s)
	{
		cout << "\nIntroduceti denumirea materiei prime: "; getline(in, s.denumireMateriePrima);
		cout << "\nIntroduceti unitatea de masura: "; in >> s.unitateMasura;
		cout << "\nIntroduceti cantitatea disponibila pe stoc: "; in >> s.cantitateStoc;
		return in;
	}
	void saveToFile(ofstream& file)
	{
		if (file.is_open()) {
			int lg = this->denumireMateriePrima.length() + 1; 
			file.write((char*)&lg, sizeof(int));
			file.write(this->denumireMateriePrima.data(), lg);
			int lg1 = this->unitateMasura.length() + 1; 
			file.write((char*)&lg1, sizeof(int));
			file.write(this->unitateMasura.data(), lg1);
			file.write((char*)&this->cantitateStoc, sizeof(float));
		}
	}
	friend bool operator<(const StocMateriePrima& s1, const StocMateriePrima& s2) {
		return s1.cantitateStoc < s2.cantitateStoc;
	}
	void saveToFile1(fstream& file)
	{
		if (file.is_open()) {
			int lg = this->denumireMateriePrima.length() + 1; 
			file.write((char*)&lg, sizeof(int));
			file.write(this->denumireMateriePrima.data(), lg);
			int lg1 = this->unitateMasura.length() + 1; 
			file.write((char*)&lg1, sizeof(int));
			file.write(this->unitateMasura.data(), lg1);
			file.write((char*)&this->cantitateStoc, sizeof(float));
		}
	}
	void restoreFromFile1(fstream& file)
	{
		int lg;
		file.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		file.read(buffer, lg);
		this->denumireMateriePrima = buffer;
		delete[]buffer;
		int lg1;
		file.read((char*)&lg1, sizeof(int));
		char* buffer1 = new char[lg1];
		file.read(buffer1, lg1);
		this->unitateMasura = buffer1;
		delete[]buffer1;
		file.read((char*)&this->cantitateStoc, sizeof(float));
	}
};
string StocMateriePrima::furnizorMateriePrima = "Carrefour";
void raport_stoc_crescator(StocMateriePrima* listaMateriiPrime, int nrMateriiPrime)
{
	StocMateriePrima aux;
	ofstream fisier;

	fisier.open("Raport_stoc_crescator_materii_prime.txt", ios::out);
	if (fisier.is_open() && nrMateriiPrime>0) {
		for (int i = 0; i < nrMateriiPrime - 1; i++) {
			for (int j = i + 1; j < nrMateriiPrime; j++) {
				if (listaMateriiPrime[i].getCantitateStoc() > listaMateriiPrime[j].getCantitateStoc())
				{
					aux = listaMateriiPrime[i];
					listaMateriiPrime[i] = listaMateriiPrime[j];
					listaMateriiPrime[j] = aux;
				}
			}
		}
		cout << "\nRaport stoc materii prime generat crescator: \n";
		for (int i = 0; i < nrMateriiPrime; i++) {
			fisier << listaMateriiPrime[i].getDenumireMateriePrima()<<" "<<listaMateriiPrime[i].getCantitateStoc()<<" "<<listaMateriiPrime[i].getUnitateMasura()<<endl;
			cout << listaMateriiPrime[i].getDenumireMateriePrima() << " " << listaMateriiPrime[i].getCantitateStoc() << " " << listaMateriiPrime[i].getUnitateMasura()<<endl;
		}
		fisier << endl;
	}
	fisier.close();
}
void raport_materii_prime_indisponibile(StocMateriePrima* listaMateriiPrime, int nrMateriiPrime)
{
	ofstream fisier;
	fisier.open("Raport_materii_prime_indisponibile.txt", ios::out);
	if (fisier.is_open() && nrMateriiPrime > 0)
	{
		cout << "\nRaport materii prime indisponibile pe stoc: \n";
		for (int i = 0; i < nrMateriiPrime; i++)
		{
			if (listaMateriiPrime[i].getCantitateStoc() == 0)
			{
				fisier << listaMateriiPrime[i].getDenumireMateriePrima()<<endl;
				cout << listaMateriiPrime[i].getDenumireMateriePrima()<<endl;
			}
		}
		fisier.close();
	}
}
class Ingredient:IFile
{
	StocMateriePrima ingredient;
	float cantitate = 0;
	int nrAlergeni = 0;
	string* alergeni = nullptr;

public:
	Ingredient()
	{}
	Ingredient(StocMateriePrima ingredient, float cantitate, int nrAlergeni, string* alergeni)
	{
		this->ingredient = ingredient;
		this->cantitate = cantitate;
		if (nrAlergeni > 0 && alergeni != nullptr)
		{
			this->nrAlergeni = nrAlergeni;
			this->alergeni = new string[this->nrAlergeni];
			for (int i = 0; i < this->nrAlergeni; i++)
				this->alergeni[i] = alergeni[i];
		}
		else
		{
			this->nrAlergeni = 0;
			this->alergeni = nullptr;
		}
	}
	Ingredient(StocMateriePrima ingredient)
	{
		this->ingredient = ingredient;
	}
	Ingredient(int nrAlergeni, string* alergeni)
	{
		if (nrAlergeni > 0 && alergeni != nullptr)
		{
			this->nrAlergeni = nrAlergeni;
			this->alergeni = new string[this->nrAlergeni];
			for (int i = 0; i < this->nrAlergeni; i++)
				this->alergeni[i] = alergeni[i];
		}
		else
		{
			this->nrAlergeni = 0;
			this->alergeni = nullptr;
		}
	}
	Ingredient(const Ingredient& i)
	{
		this->ingredient = i.ingredient;
		this->cantitate = i.cantitate;
		if (i.nrAlergeni > 0 && i.alergeni != nullptr)
		{
			this->nrAlergeni = i.nrAlergeni;
			this->alergeni = new string[this->nrAlergeni];
			for (int k = 0; k < this->nrAlergeni; k++)
				this->alergeni[k] = i.alergeni[k];
		}
		else
		{
			this->nrAlergeni = 0;
			this->alergeni = nullptr;
		}
	}
	Ingredient& operator=(const Ingredient& i) {
		if (this != &i)
		{
			delete[]this->alergeni;
			this->alergeni = nullptr;

			this->ingredient = i.ingredient;
			this->cantitate = i.cantitate;
			if (i.nrAlergeni > 0 && i.alergeni != nullptr)
			{
				this->nrAlergeni = i.nrAlergeni;
				this->alergeni = new string[this->nrAlergeni];
				for (int k = 0; k < this->nrAlergeni; k++)
					this->alergeni[k] = i.alergeni[k];
			}
			else
			{
				this->nrAlergeni = 0;
				this->alergeni = nullptr;
			}
		}
		return *this;
	}
	void setIngredient(StocMateriePrima ingredient)
	{
		if (ingredient.getDenumireMateriePrima().length()>1)
		{
			this->ingredient = ingredient;
			this->ingredient.setCantitateStoc(ingredient.getCantitateStoc());
		}
	}
	StocMateriePrima& getIngredient()
	{
		return this->ingredient;
	}
	void setCantitateIngredient(float cantitate)
	{
		if (cantitate > 0)
			this->cantitate = cantitate;
	}
	float& getCantitateIngredient()
	{
		return this->cantitate;
	}
	void setAlergeni(int nrAlergeni, string* alergeni)
	{
		delete[]this->alergeni;
		if (nrAlergeni > 0 && alergeni != nullptr)
		{
			this->nrAlergeni = nrAlergeni;
			this->alergeni = new string[this->nrAlergeni];
			for (int i = 0; i < this->nrAlergeni; i++)
				this->alergeni[i] = alergeni[i];
		}
		else
		{
			this->nrAlergeni = 0;
			this->alergeni = nullptr;
		}
	}
	string* getAlergeni()
	{
		if (this->nrAlergeni > 0 && this->alergeni != nullptr)
			return this->alergeni;
	}
	int getNrAlergeni()
	{
		return this->nrAlergeni;
	}
	
	~Ingredient() {
		delete[]this->alergeni;
		this->alergeni = nullptr;
	}

	friend ostream& operator<<(ostream& out, const Ingredient& i)
	{
		out << "\n-----------Ingredient------------";
		out << i.ingredient;
		out << "\nCantitatea ingredientului  necesara prepararii: " << i.cantitate;
		out << "\nNumarul de alergeni: " << i.nrAlergeni;
		out << "\nAlergenii: ";
		if (i.alergeni != nullptr)
			for (int k = 0; k < i.nrAlergeni; k++)
				out << i.alergeni[k] << " ";
		else
			out << "-";
		out << "\n---------------------------------\n";

		return out;
	}
	friend istream& operator>>(istream& in, Ingredient& i)
	{
		delete[]i.alergeni;
		i.alergeni = nullptr;
		cout << "\nIntroduceti ingredientul din stoc: "; in >> i.ingredient;
		cout << "\nIntroduceti cantitatea ingredientului necesara prepararii: "; in >> i.cantitate;
		cout << "\nIntroduceti numarul de alergeni: "; in >> i.nrAlergeni;
		if (i.nrAlergeni <= 0)
		{
			i.nrAlergeni = 0;
			i.alergeni = nullptr;
		}
		else
		{

			i.alergeni = new string[i.nrAlergeni];//alocare vector dinamic
			cout << "\nIntroduceti alergenii:\n";
			for (int k = 0; k < i.nrAlergeni; k++)
			{
				cout << "Alergenul " << k << ": ";
				in >> i.alergeni[k];
			}
		}
		return in;
	}

	void saveToFile1(fstream& file) {
		file.write((char*)&this->ingredient, sizeof(Ingredient::ingredient));
		file.write((char*)&this->cantitate, sizeof(float));
		file.write((char*)&this->nrAlergeni, sizeof(int));
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			int lg = this->alergeni[i].length() + 1;
			file.write((char*)&lg, sizeof(int));
			file.write(this->alergeni[i].data(), lg);
		}
	}
	void restoreFromFile1(fstream& file) {
		file.read((char*)&this->ingredient, sizeof(ingredient));
		file.read((char*)&this->cantitate, sizeof(float));
		file.read((char*)&this->nrAlergeni, sizeof(int));
		if (this->alergeni != nullptr)
		{
			delete[]this->alergeni;
			this->alergeni = nullptr;
		}
		this->alergeni = new string[this->nrAlergeni];
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			int lg;
			file.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			file.read(buffer, lg);
			this->alergeni[i] = buffer;
			delete[]buffer;
		}
	}
	
};

void raport_alergeni(Ingredient* listaIngrediente, int nrIngrediente)
{
	ofstream fisier;
	fisier.open("Raport_alergeni.txt", ios::out);
	if (fisier.is_open() && nrIngrediente > 0) {
		cout << "\nRaport ingrediente ce contin alergeni: \n";
		for (int i = 0; i < nrIngrediente; i++) {
			for (int j = 0; j < listaIngrediente[i].getNrAlergeni(); j++) {
				if (listaIngrediente[i].getAlergeni() != nullptr) {
					fisier << listaIngrediente[i].getIngredient().getDenumireMateriePrima() << ": " << listaIngrediente[i].getAlergeni()[j] << endl;
					cout << listaIngrediente[i].getIngredient().getDenumireMateriePrima() << ": " << listaIngrediente[i].getAlergeni()[j] << endl;
				}
			}
		}
	}
	fisier.close();
}
class Preparat
{
	const int idPreparat = 0;//am init cu 0 pentru a putea crea constructorul fara parametri, pt a crea vectorul listaPreparate
	string denumirePreparat = "anonima";
	float gramaj = 0;
	float pret = 0;
	int nrIngrediente = 0;
	Ingredient* listaIngrediente = nullptr; //vector alocat dinamic ce contine o lista cu ingrediente
public:
	Preparat() {}
	Preparat(int idPreparat) :idPreparat(idPreparat)
	{}
	Preparat(int idPreparat, string denumirePreparat, float gramaj, float pret, int nrIngrediente, Ingredient* listaIngrediente) :idPreparat(idPreparat)
	{
		this->denumirePreparat = denumirePreparat;
		this->gramaj = gramaj;
		this->pret = pret;
		if (listaIngrediente != nullptr && nrIngrediente > 0)
		{
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = listaIngrediente[i];
		}
		else
		{
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
	}
	Preparat(const Preparat& p) :idPreparat(p.idPreparat)
	{
		this->denumirePreparat = p.denumirePreparat;
		this->gramaj = p.gramaj;
		this->pret = p.pret;
		if (p.listaIngrediente != nullptr && p.nrIngrediente > 0)
		{
			this->nrIngrediente = p.nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = p.listaIngrediente[i];
		}
		else
		{
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
	}
	Preparat& operator=(const Preparat& p)
	{
		delete[]this->listaIngrediente;
		this->listaIngrediente = nullptr;

		if (this != &p)
		{
			this->denumirePreparat = p.denumirePreparat;
			this->gramaj = p.gramaj;
			this->pret = p.pret;
			if (p.listaIngrediente != nullptr && p.nrIngrediente > 0)
			{
				this->nrIngrediente = p.nrIngrediente;
				this->listaIngrediente = new Ingredient[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
					this->listaIngrediente[i] = p.listaIngrediente[i];
			}
			else
			{
				this->nrIngrediente = 0;
				this->listaIngrediente = nullptr;
			}
		}
		return *this;
	}
	//getteri si setteri
	void setDenumirePreparat(string denumirePreparat)
	{
		if (denumirePreparat.length() > 1)
			this->denumirePreparat = denumirePreparat;
	}
	string getDenumirePreparat()
	{
		return this->denumirePreparat;
	}
	void setGramajPreparat(float gramaj)
	{
		if (gramaj > 0)
			this->gramaj = gramaj;
	}
	float getGramajPreparat()
	{
		return this->gramaj;
	}
	void setPretPreparat(float pret)
	{
		if (pret > 0)
			this->pret = pret;
	}
	float getPretPreparat()
	{
		return this->pret;
	}
	void setNrIngrediente(int nrIngrediente)
	{
		if (nrIngrediente > 0)
			this -> nrIngrediente = nrIngrediente;
	}
	int getNrIngrediente()
	{
		return this->nrIngrediente;
	}
	void setListaIngrediente(Ingredient* listaIngrediente, int nrIngrediente)
	{
		delete[]this->listaIngrediente;
		this->listaIngrediente = nullptr;

		if (listaIngrediente != nullptr && nrIngrediente > 0)
		{
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->listaIngrediente[i] = listaIngrediente[i];
		}
		else
		{
			this->nrIngrediente = 0;
			this->listaIngrediente = nullptr;
		}
	}
	Ingredient* getListaIngrediente()
	{
		return this->listaIngrediente;
	}
	void adaugaIngredient(Ingredient ingredient)
	{
		Preparat p = *this;
		delete[]this->listaIngrediente;
		this->nrIngrediente++;
		this->listaIngrediente = new Ingredient[this->nrIngrediente];
		for (int i = 0; i < p.nrIngrediente; i++)
			this->listaIngrediente[i] = p.listaIngrediente[i];
		this->listaIngrediente[this->nrIngrediente - 1] = ingredient;
	}
	~Preparat()
	{
		delete[]this->listaIngrediente;
		this->listaIngrediente = nullptr;
	}
	friend ostream& operator<<(ostream& out, const Preparat& p)
	{
		out << "\n-----------PREPARAT------------";
		//out << "\nId-ul preparatulu: " << p.idPreparat;
		out << "\nDenumirea preparatului: " << p.denumirePreparat;
		out << "\nGramajul preparatului(grame/ml): " << p.gramaj;
		out << "\nPretul preparatului(lei): " << p.pret;
		out << "\nNumarul de ingrediente necesare pentru preparare: " << p.nrIngrediente;
		out << "\nLista ingredientelor : ";
		if (p.listaIngrediente != nullptr)
			for (int i = 0; i < p.nrIngrediente; i++)
				//afiseaza tot ingredientul cu toate atributele: out << p.listaIngrediente[i] << " ";
				out << p.listaIngrediente[i].getIngredient().getDenumireMateriePrima() << "  |  ";
		else
			out << "-";
		out << "\n------------------------------\n";
		return out;
	}
	bool existaIngredient(Ingredient& ingredientCautat)
	{
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			if (this->listaIngrediente[i].getIngredient().getDenumireMateriePrima() == ingredientCautat.getIngredient().getDenumireMateriePrima())
				return true;
		}
		return false;
	}
	friend istream& operator>>(istream& in, Preparat& p)
	{
		cout << "\nIntroduceti denumirea preparatului: "; getline(in, p.denumirePreparat);
		cout << "\nIntroduceti gramajul preparatului: "; in >> p.gramaj;
		cout << "\nIntroduceti pretul preparatului(lei): "; in >> p.pret;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Preparat& p)
	{
		getline(in, p.denumirePreparat);
		in >> p.gramaj;
		in >> p.pret;
		return in;
	}
	bool disponibilitateStoc(Preparat preparat) {

		for (int i = 0; i < this->nrIngrediente; i++)
		{
			if (preparat.getListaIngrediente()[i].getCantitateIngredient() > preparat.getListaIngrediente()[i].getIngredient().getCantitateStoc())
				return false;
		}
		return true;
	}
	void scadeCantitateStoc() {
		if (this->nrIngrediente > 0 && this->listaIngrediente != nullptr)
		{
			for (int i = 0; i < this->nrIngrediente; i++) {
				float cantitateStoc1 = this->listaIngrediente[i].getIngredient().getCantitateStoc();
				float cantitateNecesara = this->listaIngrediente[i].getCantitateIngredient();
				float cantitateNoua = cantitateStoc1 - cantitateNecesara;
				this->listaIngrediente[i].getIngredient().setCantitateStoc(cantitateNoua);
			}

		}
	}
	void saveToFile(ofstream& file)
	{
		if (file.is_open()) {
			int lg = this->denumirePreparat.length() + 1; //1-terminator de sir
			file.write((char*)&lg, sizeof(int));
			file.write(this->denumirePreparat.data(), lg);
			file.write((char*)&this->gramaj, sizeof(float));
			file.write((char*)&this->pret, sizeof(float));
		}
	}
	
};
	void raport_preturi_preparate(Preparat* listaPreparate, int nrPreparate)
	{
		ofstream fisier;

		fisier.open("Raport_preturi_preparate.txt", ios::out);
		if (fisier.is_open() && nrPreparate>0) {

			Preparat maxPreparat = listaPreparate[0];
			Preparat minPreparat = listaPreparate[0];
			for (int i = 0; i < nrPreparate; i++) {
				if (listaPreparate[i].getPretPreparat() > maxPreparat.getPretPreparat()) {
					maxPreparat = listaPreparate[i];
				}
				if (listaPreparate[i].getPretPreparat() < minPreparat.getPretPreparat()) {
					minPreparat = listaPreparate[i];
				}
			}
			cout << "\nRaport pret maxim si pret minim al preparatelor: \n";
				fisier << maxPreparat.getDenumirePreparat() << " " << maxPreparat.getPretPreparat();
				cout << maxPreparat.getDenumirePreparat() << " " << maxPreparat.getPretPreparat() << " lei -- preparatul din meniu cu pretul maxim "<< endl;
				fisier << endl;
				fisier << minPreparat.getDenumirePreparat() << " " << minPreparat.getPretPreparat();
				cout << minPreparat.getDenumirePreparat() << " " << minPreparat.getPretPreparat() << " lei -- preparatul din meniu cu pretul minim "<< endl;
			
		}
		fisier.close();
	}
enum TipMeniu
{
	Necunoscut = 10, Micdejun = 20, Pranz = 30, Cina = 40
};
class Meniu {
	TipMeniu tipMeniu = TipMeniu::Necunoscut;
	int nrPreparate = 0;
	Preparat* listaPreparate = nullptr;
public:
	Meniu() {
		//c fara param
	}
	Meniu(TipMeniu tipMeniu, int nrPreparate, Preparat* listaPreparate)
	{
		this->tipMeniu = tipMeniu;
		if (nrPreparate > 0 && listaPreparate != nullptr)
		{
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new Preparat[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = listaPreparate[i];
		}
		else {
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
	}
	Meniu(const Meniu& m)
	{

		this->tipMeniu = m.tipMeniu;
		if (m.nrPreparate > 0 && m.listaPreparate != nullptr)
		{
			this->nrPreparate = m.nrPreparate;
			this->listaPreparate = new Preparat[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = m.listaPreparate[i];
		}
		else {
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
	}
	Meniu& operator=(const Meniu& m)
	{
		if (this != &m)
		{
			delete[]this->listaPreparate;
			this->listaPreparate = nullptr;

			this->tipMeniu = m.tipMeniu;
			if (m.nrPreparate > 0 && m.listaPreparate != nullptr)
			{
				this->nrPreparate = m.nrPreparate;
				this->listaPreparate = new Preparat[this->nrPreparate];
				for (int i = 0; i < this->nrPreparate; i++)
					this->listaPreparate[i] = m.listaPreparate[i];
			}
			else {
				this->nrPreparate = 0;
				this->listaPreparate = nullptr;
			}
		}
		return *this;
	}
	//getteri si setteri
	void setTipMeniu(TipMeniu tipMeniu)
	{
		if (tipMeniu == TipMeniu::Micdejun || tipMeniu == TipMeniu::Pranz || tipMeniu == TipMeniu::Cina)
		{
			this->tipMeniu = tipMeniu;
		}
	}
	TipMeniu getTipMeniu()
	{
		return this->tipMeniu;
	}
	void setNrPreparate(int nrPreparate)
	{
		if (nrPreparate > 0)
			this->nrPreparate = nrPreparate;
	}
	int getNrPreparate()
	{
		return this->nrPreparate;
	}
	void setListaPreparate(Preparat* listaPreparate, int nrPreparate)
	{
		delete[]this->listaPreparate;
		this->listaPreparate = nullptr;
		if (listaPreparate != nullptr && nrPreparate > 0)
		{
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new Preparat[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++)
				this->listaPreparate[i] = listaPreparate[i];
		}
		else
		{
			this->nrPreparate = 0;
			this->listaPreparate = nullptr;
		}
	}
	Preparat* getListaPreparate()
	{
		return this->listaPreparate;
	}
	//metode de adaugare si afisare preparat 
	void adaugaPreparat(Preparat preparat)
	{
		Meniu m = *this;
		delete[]this->listaPreparate;
		this->nrPreparate++;
		this->listaPreparate = new Preparat[this->nrPreparate];
		for (int i = 0; i < m.nrPreparate; i++)
		{
			this->listaPreparate[i] = m.listaPreparate[i];
		}
		this->listaPreparate[this->nrPreparate - 1] = preparat;
	}
	~Meniu()
	{
		delete[]this->listaPreparate;
		this->listaPreparate = nullptr;
	}
	friend ostream& operator<<(ostream& out, const Meniu& m)
	{
		out << "\n-----------------MENIU----------------";
		out << "\nTipul meniului(Micdejun-20, Pranz-30, Cina-40): " << m.tipMeniu;
		out << "\nNumarul de preparate existente in meniu: " << m.nrPreparate;
		out << "\nLista preparatelor : ";
		out << "\n-------------------------------------";
		if (m.listaPreparate != nullptr)
			for (int i = 0; i < m.nrPreparate; i++)
			{
				out << endl << m.listaPreparate[i].getDenumirePreparat() << "  ****************  " << m.listaPreparate[i].getPretPreparat() << "   lei   ";
			}
		else
			out << "-";
		out << "\n------------------------------------\n";
		return out;
	}
	friend istream& operator>>(istream& in, Meniu& m)
	{
		in.ignore();
		string tipMeniu;
		cout << "\nIntroduceti tipul meniului(Micdejun/Pranz/Cina): "; getline(in, tipMeniu);
		while (tipMeniu != "Micdejun" && tipMeniu != "Pranz" && tipMeniu != "Cina")
		{
			cout << "\nAti introdus o denumire incorecta! Va rugam introduceti tipul meniului Micdejun/Pranz/Cina: "; getline(in, tipMeniu);

		}
		if (tipMeniu == "Micdejun")
		{
			m.tipMeniu = TipMeniu::Micdejun;
		}
		else
		{
			if (tipMeniu == "Pranz")
				m.tipMeniu = TipMeniu::Pranz;
			else
				if (tipMeniu == "Cina")
					m.tipMeniu = TipMeniu::Cina;
		}
		return in;
	}
	bool preparatInMeniu(string denumirePreparat) {
		for (int i = 0; i < this->nrPreparate; i++)
		{
			if (this->listaPreparate[i].getDenumirePreparat() == denumirePreparat)
				return true;
		}
		return false;
	}
	Preparat& getPreparatDupaDenumire(string denumirePreparat)
	{
		for (int i = 0; i < this->nrPreparate; i++)
			if (this->listaPreparate[i].getDenumirePreparat() == denumirePreparat)
				return this->listaPreparate[i];
	}
};
class Comanda
{
	const int idComanda = 0;
	string statusComanda = "Necunoscut";
	int nrPreparateComandate = 0;
	Preparat* listaPreparateComandate = nullptr;
	static Meniu meniu;
public:
	Comanda() {
	}
	Comanda(int idComanda) :idComanda(idComanda)
	{}
	Comanda(int idComanda, string statusComanda, int nrPreparateComandate, Preparat* listaPreparateComandate) :idComanda(idComanda)
	{
		this->statusComanda = statusComanda;
		if (nrPreparateComandate > 0 && listaPreparateComandate != nullptr)
		{
			this->nrPreparateComandate = nrPreparateComandate;
			this->listaPreparateComandate = new Preparat[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->listaPreparateComandate[i] = listaPreparateComandate[i];
		}
		else {
			this->nrPreparateComandate = 0;
			this->listaPreparateComandate = nullptr;
		}
	}
	Comanda(const Comanda& c) :idComanda(c.idComanda)
	{
		this->statusComanda = c.statusComanda;
		if (c.nrPreparateComandate > 0 && c.listaPreparateComandate != nullptr)
		{
			this->nrPreparateComandate = c.nrPreparateComandate;
			this->listaPreparateComandate = new Preparat[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
				this->listaPreparateComandate[i] = c.listaPreparateComandate[i];
		}
		else {
			this->nrPreparateComandate = 0;
			this->listaPreparateComandate = nullptr;
		}
	}
	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{
			delete[]this->listaPreparateComandate;
			this->listaPreparateComandate = nullptr;

			this->statusComanda = c.statusComanda;
			if (c.nrPreparateComandate > 0 && c.listaPreparateComandate != nullptr)
			{
				this->nrPreparateComandate = c.nrPreparateComandate;
				this->listaPreparateComandate = new Preparat[this->nrPreparateComandate];
				for (int i = 0; i < this->nrPreparateComandate; i++)
					this->listaPreparateComandate[i] = c.listaPreparateComandate[i];
			}
			else {
				this->nrPreparateComandate = 0;
				this->listaPreparateComandate = nullptr;
			}
		}
		return *this;
	}
	//getteri si setteri
	void setStatusComanda(string statusComanda)
	{
		if (statusComanda.length() > 0)
		{
			this->statusComanda = statusComanda;
		}
	}
	string getStatusComanda()
	{
		return this->statusComanda;
	}
	static void setMeniu(Meniu meniu)
	{
		if (meniu.getListaPreparate() != nullptr)
		{
			Comanda::meniu = meniu;
		}
	}
	static Meniu getMeniu()
	{
		return Comanda::meniu;
	}
	void setNrPreparateComandate(int nrPreparateComandate)
	{
		if (nrPreparateComandate > 0)
			this->nrPreparateComandate = nrPreparateComandate;
	}
	int getNrPreparateComandate()
	{
		return this->nrPreparateComandate;
	}
	void setListaPreparateComandate(Preparat* listaPreparateComandate, int nrPreparateComandate)
	{
		delete[]this->listaPreparateComandate;
		this->listaPreparateComandate = nullptr;
		if (listaPreparateComandate != nullptr && nrPreparateComandate > 0)
		{
			this->nrPreparateComandate = nrPreparateComandate;
			this->listaPreparateComandate = new Preparat[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++)
			{
				if (meniu.preparatInMeniu(listaPreparateComandate[i].getDenumirePreparat()))
					this->listaPreparateComandate[i] = listaPreparateComandate[i];
				else
					this->nrPreparateComandate--; //se adauga doar preparatele existente in meniu
			}
		}
		else
		{
			this->nrPreparateComandate = 0;
			this->listaPreparateComandate = nullptr;
		}
	}
	Preparat* getListaPreparateComandate()
	{
		return this->listaPreparateComandate;
	}
	//metode de adaugare si afisare preparat 
	void afisareListaPreparateComandate()
	{
		if (this->nrPreparateComandate > 0 && this->listaPreparateComandate != nullptr) {
			cout << "\nNumarul de preparate coamndate: " << this->nrPreparateComandate;
			cout << "\nPreparatele comandate: ";
			for (int i = 0; i < this->nrPreparateComandate; i++)
			{
				cout << this->listaPreparateComandate[i].getDenumirePreparat() << "  |  ";
			}
		}
		else
			throw exception("\nNu este comandat niciun preparat!");
	}
	void adaugaPreparatComandat(Preparat preparat)
	{
		if (meniu.preparatInMeniu(preparat.getDenumirePreparat()))
		{
			Comanda c= *this;
			delete[]this->listaPreparateComandate;
			//this->nrPreparateComandate++;
			this->listaPreparateComandate = new Preparat[this->nrPreparateComandate + 1];
			for (int i = 0; i < c.nrPreparateComandate; i++)
				this->listaPreparateComandate[i] = c.listaPreparateComandate[i];
			this->listaPreparateComandate[this->nrPreparateComandate] = preparat;

		}
		else
			cout << "\nPreparatul pe care doriti sa il adaugati nu exista in meniu!";
	}
	~Comanda()
	{
		delete[]this->listaPreparateComandate;
		this->listaPreparateComandate = nullptr;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c)
	{
		out << "\n--------COMANDA--------";
		out << "\nID comanda: " << c.idComanda;
		out << "\nStatus comanda: " << c.statusComanda;
		out << "\nNumarul de preparate comandate: " << c.nrPreparateComandate;
		out << "\nLista preparatelor comandate : ";
		if (c.listaPreparateComandate != nullptr)
			for (int i = 0; i < c.nrPreparateComandate; i++)
			{
				out << c.listaPreparateComandate[i].getDenumirePreparat() << "  |  ";
			}
		else
			out << "-";
		out << "\nPret total comanda: " << c.pretTotal() << " lei.";
		out << "\n----------------------------\n";

		return out;
	}
	friend istream& operator>>(istream& in, Comanda& c)
	{
		delete[]c.listaPreparateComandate;
		c.listaPreparateComandate = nullptr;
		cout << Comanda::meniu;
		cout << "\nIntroduceti statusul comenzii "; in >> c.statusComanda;
		cout << "\nIntroduceti numarul total de preparate pe care doriti sa le comandati: "; in >> c.nrPreparateComandate;
		in.ignore();
		if (c.nrPreparateComandate <= 0)
		{
			c.nrPreparateComandate = 0;
			c.listaPreparateComandate = nullptr;
		}
		else
		{

			c.listaPreparateComandate = new Preparat[c.nrPreparateComandate];
			for (int i = 0; i < c.nrPreparateComandate; i++)
			{
				string denumirePrepComanda;
				cout << "\nIntroduceti denumirea preparatului pe care doriti sa il comandati: "; getline(in, denumirePrepComanda);
				bool preparatGasit = false;
				while (!c.meniu.preparatInMeniu(denumirePrepComanda))
				{
					cout << "\nPreparatul " << denumirePrepComanda << " nu exista in meniu! Alegeti altul!";
					cout << "\nIntroduceti denumirea preparatului pe care doriti sa il comandati: "; getline(in, denumirePrepComanda);
				}
				if (c.meniu.preparatInMeniu(denumirePrepComanda))
				{
					Preparat preparat = c.meniu.getPreparatDupaDenumire(denumirePrepComanda);
					if (preparat.disponibilitateStoc(preparat))
					{
						c.listaPreparateComandate[i] = preparat;
						c.meniu.getPreparatDupaDenumire(preparat.getDenumirePreparat()).scadeCantitateStoc();
						preparatGasit = true;
					}
					else
					{
						cout << "\nPreparatul " << denumirePrepComanda << " nu este disponibil in stoc!Va rugam alegeti altul!";
					}
				}
				if (!preparatGasit)
					i--;

			}
			cout << "\n!!!!!!!COMANDA DVS A FOST PRELUATA CU SUCCES!!!!!!!!\n";
		}
		return in;
	}
	float pretTotal()const
	{
		float pret = 0;
		for (int i = 0; i < this->nrPreparateComandate; i++)
		{
			pret += this->listaPreparateComandate[i].getPretPreparat();
		}
		return pret;
	}
};
Meniu Comanda::meniu;
void raport_preparate_comandate(Comanda c)
{
	ofstream fisier;
	fisier.open("Raport_preparate_comandate.txt", ios::out);
	if (fisier.is_open() && c.getNrPreparateComandate() > 0) {

		Preparat maxPreparat = c.getListaPreparateComandate()[0];
		for (int i = 0; i < c.getNrPreparateComandate(); i++) {
			if (c.getListaPreparateComandate()[i].getPretPreparat() > maxPreparat.getPretPreparat()) {
				maxPreparat = c.getListaPreparateComandate()[i];
			}
		}
		cout << "\nRaport preparat comandat cu pretul maxim: ";
		fisier << maxPreparat.getDenumirePreparat() << " " << maxPreparat.getPretPreparat();
		cout << maxPreparat.getDenumirePreparat() << " " << maxPreparat.getPretPreparat() << endl;
	}
	fisier.close();
}
void raport_nr_plasare_comanda(int k)
{
	cout << "\nNumarul de comenzi plasate: " << k << endl;
}
void raport_comenzi(ifstream& file, char delimitator) {
	if (file.is_open())
	{
		//int k = 0;
		string linieCSV;
		string antet;
		getline(file, antet);
		while (getline(file, linieCSV))
		{
			if (linieCSV.empty())
			{
				cout << "\nNu exista inregistrari!";
			}
			else {
				string cheie;
				string nrPreparateComandate;
				string status;
				istringstream linieStream(linieCSV);
				getline(linieStream, cheie, delimitator);
				getline(linieStream, nrPreparateComandate, delimitator);
				getline(linieStream, status);
				//linieStream >> cheie >> delimitator >> nrPreparateComandate >> delimitator >> status;

				//afisare:
				cout << "Nr comanda: " << cheie << "--> numar preparate comandate: " << nrPreparateComandate << "--> status comanda: " << status << endl;

			}
		}
		file.close();
	}
	else cout << "\nNu s-a putut deschide fisierul!";


}
int main(int argc, char * argv[]) {
	
	char fisier1[100]; //numele fisierelor 
	char fisier2[100];
	if (argc == 3)
	{
		cout << "Numarul de argumente: " << argc << endl;
		for (int i = 0; i < argc; i++)
		{
			cout << "Argument " << i << ": " << argv[i] << endl;
		}
		strcpy(fisier1, argv[1]);//primul argument e numele primului fisier
		strcpy(fisier2, argv[2]);
	}
	else
	{
		strcpy(fisier1, "Stoc_materie_prima.txt");//se folosesc numele fisierelor implicite
		strcpy(fisier2, "Preparate.txt");
	}
	//CLASA STOC MATERIE PRIMA 
	StocMateriePrima* listaStocMateriePrima;
	int nrMateriiPrime = 0;
	listaStocMateriePrima = new StocMateriePrima[nrMateriiPrime];
	ifstream date_stoc_materie_prima(fisier1, ios::in); //preia datele din fisier
	if (date_stoc_materie_prima.is_open()) {
		date_stoc_materie_prima >> nrMateriiPrime;

		listaStocMateriePrima = new StocMateriePrima[nrMateriiPrime];
		for (int i = 0; i < nrMateriiPrime; i++)
		{
			string denumireMateriePrima; date_stoc_materie_prima >> denumireMateriePrima;
			string unitateMasura; date_stoc_materie_prima >> unitateMasura;
			float cantitateStoc; date_stoc_materie_prima >> cantitateStoc;

			listaStocMateriePrima[i].setDenumireMateriePrima(denumireMateriePrima);
			listaStocMateriePrima[i].setUnitateMasura(unitateMasura);
			listaStocMateriePrima[i].setCantitateStoc(cantitateStoc);
		}
		date_stoc_materie_prima.close();
	}
	//	cout << "\nLista de materii prime: ";
	set<StocMateriePrima> setMateriePrima;
	for (int i = 0; i < nrMateriiPrime; i++)
	{
		setMateriePrima.insert(listaStocMateriePrima[i]);
	//	cout << listaStocMateriePrima[i];
	}set<StocMateriePrima>::iterator itSet;
	//for (itSet = setMateriePrima.begin(); itSet != setMateriePrima.end(); itSet++)
	//	cout << *itSet << endl;

	ofstream backup_stoc_materie_prima;//scrie date in fisier
	backup_stoc_materie_prima.open("Backup_stoc_materie_prima.bin", ios::out | ios::binary);
	if (backup_stoc_materie_prima.is_open()) {
		backup_stoc_materie_prima.write((char*)&nrMateriiPrime, sizeof(int));

		for (int i = 0; i < nrMateriiPrime; i++)
			listaStocMateriePrima[i].saveToFile(backup_stoc_materie_prima);
		backup_stoc_materie_prima.close();
		cout << "\nBackup fisier Stoc_materie_prima realizat cu succes!";
	}
	//citire si scriere in fisiere binare
	/*fstream file("Stoc_materie_prima_virt.bin", ios::out | ios::binary);
	for (int i = 0; i < nrMateriiPrime; i++)
	{
		listaStocMateriePrima[i].saveToFile1(file);
	}file.close();
	fstream file("Stoc_materie_prima_virt.bin", ios::in | ios::binary);
	for (int i = 0; i < nrMateriiPrime; i++)
	{
		listaStocMateriePrima[i].restoreFromFile1(file);
		cout << listaStocMateriePrima[i]<<endl;
	}file.close();*/

	//CLASA INGREDIENT
	string alergeni[] = { "ou", "vitaminaA", "vitaminaC" };
	vector<Ingredient> vIngredient;
	Ingredient i1(listaStocMateriePrima[0], 20, 0, alergeni); vIngredient.push_back(i1);
	Ingredient i2(listaStocMateriePrima[1], 2, 1, alergeni); vIngredient.push_back(i2);
	Ingredient i3(listaStocMateriePrima[2], 20, 0, alergeni); vIngredient.push_back(i3);

	string alergeni1[] = { "vitaminaA", "vitaminaB" };
	Ingredient i4(listaStocMateriePrima[3], 20, 0, alergeni1); vIngredient.push_back(i4);
	Ingredient i5(listaStocMateriePrima[4], 5, 1, alergeni1); vIngredient.push_back(i5);
	Ingredient i6(listaStocMateriePrima[5], 20, 0, alergeni); vIngredient.push_back(i6);
	Ingredient i7(listaStocMateriePrima[6], 10, 0, alergeni); vIngredient.push_back(i7);
	Ingredient i8(listaStocMateriePrima[7], 20, 1, alergeni1); vIngredient.push_back(i8);
	Ingredient i9(listaStocMateriePrima[8], 15, 1, alergeni1); vIngredient.push_back(i9);
	Ingredient i10(listaStocMateriePrima[9], 1, 0, alergeni); vIngredient.push_back(i10);
	Ingredient i11(listaStocMateriePrima[10], 12, 0, alergeni); vIngredient.push_back(i11);
	vector<Ingredient>::iterator itI;
	//for (itI = vIngredient.begin(); itI != vIngredient.end(); itI++)
	//cout << *itI<< endl;
	//citire si scriere in fisiere binare
	/*fstream file("Ingrediente.bin", ios::out | ios::binary);
	for (itI = vIngredient.begin(); itI != vIngredient.end(); itI++)
	{
		itI->saveToFile1(file);
	}
	file.close();
	fstream file("Ingrediente.bin", ios::in | ios::binary);
	if (file.is_open()) {
		for (itI = vIngredient.begin(); itI != vIngredient.end(); itI++)
		{
			itI->restoreFromFile1(file);
			cout << *itI << endl;
		}
		file.close();
	}*/
	Ingredient listaIngr[] = { i1,i2,i3,i4,i5,i6,i7,i8,i9 };
	//CLASA PREPARAT
	Preparat* listaPreparate;
	int nrPreparate = 0;
	listaPreparate = new Preparat[nrPreparate];
	ifstream date_preparate(fisier2, ios::in);
	if (date_preparate.is_open()) {
		date_preparate >> nrPreparate;
		listaPreparate = new Preparat[nrPreparate];
		for (int i = 0; i < nrPreparate; i++)
		{
			
			string denumirePreparat; date_preparate >> denumirePreparat;
			float gramaj; date_preparate >> gramaj;
			float pret; date_preparate >> pret;
			int nrIngrediente; date_preparate >> nrIngrediente;
			
			listaPreparate[i].setDenumirePreparat(denumirePreparat);
			listaPreparate[i].setGramajPreparat(gramaj);
			listaPreparate[i].setPretPreparat(pret);
			listaPreparate[i].setNrIngrediente(nrIngrediente);
			
			Ingredient listaIngrediente1[] = { i2, i4, i5 };
			Ingredient listaIngrediente2[] = { i4, i5 };
			listaPreparate[0].setListaIngrediente(listaIngrediente1,3);
			listaPreparate[1].setListaIngrediente(listaIngrediente2, 2);
			Ingredient listaIngrediente3[] = { i1, i6, i7,i10 };
			listaPreparate[2].setListaIngrediente(listaIngrediente3, 2);
			listaPreparate[3].setListaIngrediente(listaIngrediente3, 4);
		}
		date_preparate.close();
	}
	ofstream backup_preparate;
	backup_preparate.open("Backup_preparate.bin", ios::out | ios::binary);
	if (backup_preparate.is_open()) {
		backup_preparate.write((char*)&nrPreparate, sizeof(int));
		for (int i = 0; i < nrPreparate; i++)
			listaPreparate[i].saveToFile(backup_preparate);
		backup_preparate.close();
		cout << "\nBackup fisier Preparate realizat cu succes!";
	}
	//cout << "\nLista de preparate: ";
	//for (int i = 0; i < nrPreparate; i++)
	//	cout << listaPreparate[i] << endl;

	//CLASA MENIU
	Meniu m1(TipMeniu::Pranz, 4, listaPreparate);
	//cout << m1;

	//CLASA COMANDA
	Comanda c1(1, "Preluare", 4, listaPreparate);
	Comanda c2(2, "Procesare", 2, listaPreparate);
	c1.setMeniu(m1);
	map<int, Comanda> mapComanda;
	
	//optiuni---------------
	int optiune = -1;
	int k = 0;
	while (optiune != 0)
	{
		cout << "\n\nAlegeti optiunea pe care doriti sa o efectuati:";
		cout << "\n1.Generare raport stoc materie prima crescator.";
		cout << "\n2.Generare pret maxim si pret minim al preparatelor";
		cout << "\n3.Generare materii prime indisponibile din stoc";
		cout << "\n4.Genereare raport ingrediente care contin alergeni.";
		cout << "\n5.Plasati o comanda.Generare raport pret maxim preparat comandat";
		cout << "\n6.Afisare numar de comenzi plasate.";
		cout << "\n7.Raport comenzi CSV.";
		cout << "\n8.EXIT";
		cout << "\nIntroduceti optiunea: ";
		cin >> optiune;
		if (optiune == 1) { raport_stoc_crescator(listaStocMateriePrima, nrMateriiPrime); }
		else {
			if (optiune == 2) { raport_preturi_preparate(listaPreparate, nrPreparate); }
			else
				if (optiune == 3) { raport_materii_prime_indisponibile(listaStocMateriePrima, nrMateriiPrime); }
				else
					if (optiune == 4) { raport_alergeni(listaIngr, 9); }
					else
						if (optiune == 5) {
							Comanda comanda;
							cin >> comanda;
							k++;
							mapComanda[k] = comanda;
							cout << comanda;
						
							//fisier CSV----------
							map<int, Comanda>::iterator itMap;
							ofstream date_comenzi("Comenzi.csv", ios::out);
							if (date_comenzi.is_open())
							{
								date_comenzi << "Cheie|NrPreparateComandate|StatusComanda\n";
								for (itMap = mapComanda.begin(); itMap != mapComanda.end(); itMap++)
									date_comenzi << itMap->first << "|" << itMap->second.getNrPreparateComandate() << "|" << itMap->second.getStatusComanda() << endl;
								date_comenzi.close();
								cout << "\nFisierul csv s-a actualizat cu succes!\n";
							}
							else cout << "\nNu s-a putut deschide fisierul csv!";
							
							raport_preparate_comandate(mapComanda[k]);
						}
						else

							if (optiune == 6)
							{
								raport_nr_plasare_comanda(k);
							}
	
							else if (optiune == 7)
							{
								ifstream comenzi("Comenzi.csv", ios::in);
								if (comenzi.is_open()) {
									raport_comenzi(comenzi, '|');
								}
								else cout << "\nNu s-a putut deschide fisierul csv!!";
								
							}
								else if (optiune == 8) {
									cout << "\nEXIT\n"; optiune = 0;
							}
							else cout << "\nNu ati ales o optiune valida!";
		}
	}
	return 0;
}