// moodmade.cpp 
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <filesystem>

const int ARRAYSIZE = 20;


class MoodEntry
{
public:
	MoodEntry();
	MoodEntry(std::string date, int rating, std::string note);
	std::string getDate() const;
	int getRating() const;
	std::string getNote() const;
	void entry();
	void printEntry() const;
	void setDate(std::string datet ="unspecified");
	void setRating(int ratingt =3);
	void setNote(std::string notet= "no Note");
	bool set;// set bit flag for efficiency in reading
	std::string getMoodLabel() const;
private:
	int rating;
	std::string note, date;
};

std::string MoodEntry::getMoodLabel() const {
	switch (getRating())
	{
	case 1 :
		return "Very Bad";
	case 2:
		return "Bad";
	case 3:
		return "Okay";
	case 4:
		return "Good";
	case 5:
		return "Great";
	default:
		break;
	}
};

MoodEntry::MoodEntry()
{
	setDate();
	setNote();
	setRating();
	set = false;
};

MoodEntry::MoodEntry(std::string da, int rat, std::string no)
{
	setDate(da);
	setNote(no);
	setRating(rat);
	set = true;
};
void MoodEntry::setDate(std::string datet ) {
	date = datet;
};
void MoodEntry::setRating(int ratingt) {
	if (ratingt > -1 && ratingt < 6) {
		rating = ratingt;
	}
	else
	{
		rating = 3;
	};
};
void MoodEntry::setNote(std::string notet ) {
	note = notet;
}
std::string MoodEntry::getDate() const {
	return date;
};
std::string MoodEntry::getNote() const {
	return note;
};
int MoodEntry::getRating() const {
	return rating;
};
void MoodEntry::printEntry() const {
	std::cout << date << " rating :" << getMoodLabel() << " note " << note << '\n';
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

void MoodEntry::entry() {
	std::cout << "date :";
	std::string temp;
	std::cin >> temp;
	setDate(temp);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "rating :";
	int temp1;
	while (true) {
		std::cin >> temp1;
		//This forces an integer eventually
		if (std::cin.fail())
		{
			std::cout << "Error: Conversion to integer failed!\n enter a Number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (temp1 < 1 || temp1 > 5) {

			std::cout << "Error: Number Out Of Range!\n 1 - 5 Are Valid Ratings\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}

		else {

			break;
		};
	};

	setRating(temp1);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "note :";
	std::string temp2;
	getline(std::cin, temp2);
	setNote(temp2);
	
	set = true;
};

// watcher class
class MoodTracker
{
public:
	MoodTracker();
	
	void addEntry( MoodEntry& entry);

	void displayEntries() const;

	double calculateAverage() const;

	MoodEntry getHighestMood() const;

	MoodEntry getLowestMood() const;

	int getEntryCount() const;

private:
	MoodEntry entries[ARRAYSIZE];
	int entryCount;
};
MoodTracker::MoodTracker() {
	entryCount = 0;
};
void MoodTracker::addEntry( MoodEntry& entry) {
	entry.entry();
	entries[entryCount] = entry;
	entryCount++;
};
void MoodTracker::displayEntries() const {
	for (MoodEntry var : entries)
	{
		if (var.set) {
			var.printEntry();

		}
		else
		{
			break;
		}
	};
};
double MoodTracker::calculateAverage() const {
	int acc = 0;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			acc += entries[v].getRating();


		}
		else
		{
			if (v != 0) {
				return acc / v;
			}
			return 0;
		}

	};
};
MoodEntry MoodTracker::getHighestMood() const {
	int acc = 0;
	int high = 0;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			if (entries[v].getRating() > high) {
				high = entries[v].getRating();
				acc = v;
			};


		}
		else
		{
			return entries[acc];

		};

	};
};
MoodEntry MoodTracker::getLowestMood() const {
	int acc = 0;
	int high = 90;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			if (entries[v].getRating() < high) {
				high = entries[v].getRating();
				acc = v;
			};


		}
		else
		{
			return entries[acc];

		};

	};
}
int MoodTracker::getEntryCount() const {
	return entryCount;
};




class WellnessEntry : public MoodEntry
{
public:
	WellnessEntry();
	void sleepSet(double x);
	void exeSet(int x);
	const double sleepGet();
	const int exeGet();
	void printsuEntry();
	void suEntry();
	std::string exp();
	void setupFFile(std::string ex, std::string s, std::string r, std::string d, std::string n,std::string se );
private:
	double sleepHours;
	int ExerciseMinutes;
};
std::string WellnessEntry::exp() {
	std::string def = std::to_string(exeGet()) + "|" + std::to_string(sleepGet()) + "|" + std::to_string(getRating()) + "|" + getDate() + "|" + getNote() + "|" + std::to_string(set) + "|";
	return def;
}
void WellnessEntry::setupFFile(std::string ex, std::string s, std::string r, std::string d, std::string n, std::string se) {
	exeSet(std::stoi(ex));
	sleepSet(std::stod(s));
	setRating(std::stoi(r));
	setDate(d);
	setNote(n);
	set = std::stoi(se);

};


void WellnessEntry::suEntry() {
	std::cout << "enter sleep number : ";
	int temp1;
	while (true) {
		std::cin >> temp1;
		//This forces an integer eventually
		if (std::cin.fail())
		{
			std::cout << "Error: Conversion to integer failed!\n enter a Number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (temp1 < 0 || temp1 > 24) {

			std::cout << "Error: Number Out Of Range!\n 0 - 24 Are Valid Ratings\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}

		else {

			break;
		};
	};
		sleepSet(temp1);
		std::cout << "enter excercise number : ";
		while (true) {
			std::cin >> temp1;
			//This forces an integer eventually
			if (std::cin.fail())
			{
				std::cout << "Error: Conversion to integer failed!\n enter a Number\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (temp1 < 0 || temp1 > 1440) {

				std::cout << "Error: Number Out Of Range!\n 1 - 1440 Are Valid Ratings\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}

			else {

				break;
			};
			exeSet(temp1);
			
		}
	 entry();
	}


void WellnessEntry::printsuEntry() {
	std::cout << "Sleep Hours : " << sleepGet() << " Excercise Minutes : " << exeGet();
	printEntry();
}
void WellnessEntry::sleepSet(double x) {
	if (x <= 24 && x >= 0) {
		sleepHours = x;
	}
	else {
		std::cout << "Sleep hours are out of range please enter a number between 0-24 \n";
	};
};
void WellnessEntry::exeSet(int x) {
	if (x <= 1440 && x >= 0) {
		ExerciseMinutes = x;
	}
	else {
		std::cout << "Sleep hours are out of range please enter a number between 0-1440 \n";
	};
};
double const WellnessEntry::sleepGet() {
	return sleepHours;
};
int const WellnessEntry::exeGet() {
	return ExerciseMinutes;
};


WellnessEntry::WellnessEntry()
{
	sleepHours = 0;
	ExerciseMinutes = 0;
	setDate();
	setRating();
	setNote();
}






class WellTracker
{
public:
	WellTracker();

	void addEntry(WellnessEntry& entry);

	void displayEntries() const;

	double calculateAverage() const;

	WellnessEntry getHighestMood() const;

	WellnessEntry getLowestMood() const;

	int getEntryCount() const;
	void setEntrycount(int v);

	void saveFile();
	void loadFile();
	std::string Conversion();

private:
	WellnessEntry entries[ARRAYSIZE];
	int entryCount;
};
WellTracker::WellTracker() {
	entryCount = 0;
};
void WellTracker::setEntrycount(int v) {
	entryCount = v;
}


void WellTracker::addEntry(WellnessEntry& entry) {
	entry.suEntry();
	entries[entryCount] = entry;
	entryCount++;
};
void WellTracker::displayEntries() const {
	for (WellnessEntry var : entries)
	{
		if (var.set) {
			var.printsuEntry();

		}
		else
		{
			break;
		}
	};
};
double WellTracker::calculateAverage() const {
	int acc = 0;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			acc += entries[v].getRating();


		}
		else
		{
			if (v != 0) {
				return acc / v;
			}
			return 0;
		}

	};
};
WellnessEntry WellTracker::getHighestMood() const {
	int acc = 0;
	int high = 0;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			if (entries[v].getRating() > high) {
				high = entries[v].getRating();
				acc = v;
			};


		}
		else
		{
			return entries[acc];

		};

	};
};


WellnessEntry WellTracker::getLowestMood() const {
	int acc = 0;
	int high = 90;
	for (int v = 0;v < ARRAYSIZE;v++)
	{
		if (entries[v].set) {
			if (entries[v].getRating() < high) {
				high = entries[v].getRating();
				acc = v;
			};


		}
		else
		{
			return entries[acc];

		};

	};
}
int WellTracker::getEntryCount() const {
	return entryCount;
};
std::string WellTracker::Conversion() {
	std::string Hold = "";
	for (int i = 0;i<ARRAYSIZE;i++)
	{
		Hold.append(entries[i].exp());
	}
	return Hold;
}




void WellTracker::saveFile() {
	std::ofstream EntDisk;
	EntDisk.open("Entries.txt");
	EntDisk.write(Conversion().c_str(), sizeof entries);

};

void WellTracker::loadFile() {
	std::ifstream EntDisk;
	EntDisk.open("Entries.txt");
	std::string a[6];
	int count = 0;
	

	for (int i = 0; i < ARRAYSIZE; i++)
	{
		for (int x = 0; x < 6;x++) {
			std::getline(EntDisk, a[x], '|');
		}
		if (a[5] == "0") {
			setEntrycount(count);
			break;
		};
		entries[i].setupFFile(a[0], a[1], a[2], a[3], a[4], a[5]);
		count++;

	};

	
	

};



char menu[] = "\n 1 Add entry, 2 View entries, 3 View average rating, 4 Get Highest mood, 5 Get Lowest Mood, 6 Save file, 7 Load file, 8 Exit.\n";




int cursor = 0;
WellnessEntry moods[ARRAYSIZE];
WellTracker moTr;

// process loop
void loop(){
	std::cout << menu;
	int value; 
	std::cin >> value;
	WellnessEntry x;
	switch (value)
	{
	case 1:
		moTr.addEntry(x);
		break;

	case 2:
		moTr.displayEntries();
		break;
	case 3:
		std::cout << moTr.calculateAverage();
		break;
	case 4:
		moTr.getHighestMood().printsuEntry();
		break;
	case 5:
		moTr.getLowestMood().printsuEntry();
		break;
	case 6:
		moTr.saveFile();
		break;
	case 7:
		moTr.loadFile();
		break;
	default:
		exit(EXIT_SUCCESS);
	};



}


int main() {
	if (!std::filesystem::exists("Entries.txt")) {
		std::ofstream create("Entries.txt");
		create.close();
	};

	{
		while (true)
		{
			loop();
		}



	}
}
