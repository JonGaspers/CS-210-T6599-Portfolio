/*
 * Name: 		Jonathon Gaspers
 * Date: 		08/10/2020
 * Class:		CS-210-T6599
 * Description: This is the main file for the zoo system. I tried to get multiple header/class files to work, but kept failing to get them to load properly into a single vector.
 * 				Decided to go with a struct as I am confortable with this and it helps keep things organized. If you could please email (jonathon.gaspers@snhu.edu) me an example
 * 				of how to load different object types into a single vector, I would greatly appreciate it as I spent many hours trying to figure it out, even tried using unique_ptr
 * 				and other types of ptrs	to no avail. Also, the error that appears on the icon for this .cpp file is because Eclipse has some kind of problem with the std::swap in
 * 				the RemoveAnimal() function. Program builds properly and runs so I have no idea how to fix that Eclipse error.
 */

#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <jni.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

//struct to hold animal information
struct zooAnimals {
	int trackingNum, numEggs, nursing;
	string name, type, subType;
};

//display each animal in a certain format
void DisplayAnimal(zooAnimals animal) {
	printf("%06d", animal.trackingNum);
	cout << setw(8) << setfill(' ') << " | ";
	cout << setw(15) << setfill(' ') << left << animal.name << " |";
	cout << setw(15) << setfill(' ') << left << animal.type << " |";
	cout << setw(15) << setfill(' ') << left << animal.subType << " |";
	cout << setw(15) << setfill(' ') << left << animal.numEggs << " |";
	cout << setw(15) << setfill(' ') << left << animal.nursing << " |" << endl;

}

//loads data from zoodata.txt
vector<zooAnimals> LoadDataFromFile()
{
	 vector<zooAnimals> zoo;
     fstream zooData;
     zooData.open("zoodata.txt", ios::in);

     try {
    	 while (!zooData.eof()) {
    		 zooAnimals animal;
    		 zooData >> animal.trackingNum;
    		 zooData >> animal.name;
    		 zooData >> animal.type;
    		 zooData >> animal.subType;
    		 zooData >> animal.numEggs;
    		 zooData >> animal.nursing;

    		 zoo.push_back(animal); //adds each animal to the vector
    	 }
    	 cout << "Load complete." << endl;
    	 zooData.close(); //make sure to close file before moving on
     } catch (int x) {
    	 cout << "Error when collecting data from file." << endl << x << endl;
     }

     return zoo; //returns vector with updated info from file
}

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

//adds an animal to the vector
zooAnimals AddAnimal()
{
	//temporary variables to hold input
	zooAnimals animalInfo;
	bool trackingLoop = true;
	int tempTrackingNum = 0;
	bool nameLoop = true;
	string tempName = "";
	bool typeLoop = true;
	string tempType = "";
	bool subTypeLoop = true;
	string tempSubType = "";
	bool eggLoop = true;
	int tempEggs = 0;
	bool nursingLoop = true;
	int tempNursing = 0;
	//Input verification loops for tracking number, name, type, subtype, eggs, and nursing.
	try {
		while(trackingLoop == true) {
			cout << "Enter tracking number: ";
			cin >> tempTrackingNum;
			if (tempTrackingNum > 999999 || tempTrackingNum < 0) {
				cout << "Please enter a valid tracking number." << endl;
			}
			else {
				trackingLoop = false;
			}
		}
	} catch (int x) {
		cout << "Error when collecting data from user. Please try again." << endl; //If you got here then something seriously went wrong.
	}
	try {
		while(nameLoop == true) {
			cout << "Enter animal name: ";
			cin >> tempName;
			if (tempName.length() > 15 || tempName.length() == 0) {
				cout << "Please enter a valid name." << endl;
			}
			else {
				nameLoop = false;
			}
		}
	} catch (int x) {
		cout << "Error when collecting data from user. Please try again." << endl;
	}
	try {
		while(typeLoop == true) {
			cout << "Enter animal type: ";
			cin >> tempType;

			if (tempType == "Mammal" || tempType == "Oviparous") {
				typeLoop = false;
			}
			else if (tempType == "mammal" || tempType == "oviparous") {
				if (tempType == "mammal") {
					tempType = "Mammal";
				}
				else if (tempType == "oviparous") {
					tempType = "Oviparous";
				}
				typeLoop = false;
			}
			else {
				cout << "Please enter a valid type. Acceptable types are: Mammal and Oviparous." << endl;
			}
		}
	} catch (int x) {
		cout << "Error when collecting data from user. Please try again." << endl;
	}
	try {
		while(subTypeLoop == true) {
			cout << "Enter animal sub-type: ";
			cin >> tempSubType;

			if (tempType == "Mammal") {
				if (tempSubType == "Bat" || tempSubType == "bat") {
					tempSubType = "Bat";
					subTypeLoop = false;
				}
				else if (tempSubType == "Whale" || tempSubType == "whale") {
					tempSubType == "Whale";
					subTypeLoop = false;
				}
				else if (tempSubType == "SeaLion" || tempSubType == "sealion") {
					tempSubType = "SeaLion";
					subTypeLoop = false;
				}
				else {
					cout << "Please enter a valid sub-type. Acceptable sub-types for Mammal are: Bat, Whale and SeaLion." << endl;
				}
			}
			else if (tempType == "Oviparous") {
				if (tempSubType == "Crocodile" || tempSubType == "crocodile") {
					tempSubType = "Crocodile";
					subTypeLoop = false;
				}
				else if (tempSubType == "Goose" || tempSubType == "goose") {
					tempSubType = "Goose";
					subTypeLoop = false;
				}
				else if (tempSubType == "Pelican" || tempSubType == "pelican") {
					tempSubType = "Pelican";
					subTypeLoop = false;
				}
				else {
					cout << "Please enter a valid sub-type. Acceptable sub-types for Oviparous are: Crocodile, Goose, and Pelican." << endl;
				}
			}
		}
	} catch (int x) {
		cout << "Error when collecting data from user. Please try again." << endl;
	}
	if (tempType == "Mammal") {
		try {
			while(nursingLoop == true) {
				cout << "Enter 1 if nursing, 0 if not: ";
				cin >> tempNursing;

				if (tempNursing < 0 || tempNursing > 1) {
					cout << "Please enter 1 if animal is nursing, 0 if animal is not nursing." << endl;
				}
				else {
					nursingLoop = false;
				}
			}
		} catch (int x) {
			cout << "Error when collecting data from user. Please try again." << endl;
		}
	}
	else if (tempType == "Oviparous") {
		try {
			while(eggLoop == true) {
				cout << "Enter number of eggs the animal has: ";
				cin >> tempEggs;

				if (tempEggs < 0) {
					cout << "Please enter a valid number of eggs." << endl;
				}
				else {
					eggLoop = false;
				}
			}
		} catch (int x) {
			cout << "Error when collecting data from user. Please try again." << endl;
		}
	}
	//verify user wants to add animal data.
	cout << "Are you sure you want to save the following animal info: " << endl;
	cout << setw(6) << setfill('0') << tempTrackingNum << setw(15) << setfill(' ') << tempName;
	cout << setw(15) << setfill(' ') << tempType << setw(15) << setfill(' ') << tempSubType;
	cout << setw(6) << setfill(' ') << tempEggs << setw(6) << setfill(' ') << tempNursing << endl;
	cout << "Y for yes, N to cancel adding animal: ";
	string addConfirm = "";
	cin >> addConfirm;
	bool addConfirmLoop = true;
	try {
		while(addConfirmLoop == true) {
			if (addConfirm == "Y") {
				cout << "Animal Added." << endl;
				animalInfo.trackingNum = tempTrackingNum;
				animalInfo.name = tempName;
				animalInfo.type = tempType;
				animalInfo.subType = tempSubType;
				animalInfo.numEggs = tempEggs;
				animalInfo.nursing = tempNursing;
				return animalInfo;
			} else if (addConfirm == "y") {
				cout << "Animal Added." << endl;
				animalInfo.trackingNum = tempTrackingNum;
				animalInfo.name = tempName;
				animalInfo.type = tempType;
				animalInfo.subType = tempSubType;
				animalInfo.numEggs = tempEggs;
				animalInfo.nursing = tempNursing;
				return animalInfo;
			} else if (addConfirm == "N") {
				cout << "Adding animal Cancelled." << endl;
				return animalInfo;
			}
			else if (addConfirm == "n") {
				cout << "Adding animal Cancelled." << endl;
				return animalInfo;
			} else { cout << "Please enter Y to add animal or N to cancel." << endl; }
		}
	} catch (int x) { cout << "Something went wrong, please try again." << endl; }
	return animalInfo;
}

//removes an animal from the vector
vector<zooAnimals> RemoveAnimal(int trackingNum, vector<zooAnimals> animals)
{
	for(unsigned int i = 0; i < animals.size(); ++i) {			//look for given animal tracking #
		if (animals.at(i).trackingNum == trackingNum) {			//if found then confirm it's the correct animal to be removed
			string confirm = "";
			bool loop = true;
			try {
				while(loop == true) {
					cout << "Are you sure you want to remove " << animals.at(i).name << " with tracker number: " << animals.at(i).trackingNum << " from the zoo? Y for yes, N for no: ";
					cin >> confirm;
					if (confirm.compare("Y") == 0) {		//if correct animal to be removed, swap animal to end of the vector, then delete
						std::swap(animals.at(i), animals.back());
						animals.pop_back();
						cout << "Animal successfully deleted." << endl;
						return animals;
						loop = false;
					}
					else if (confirm == "N") { 				//if incorrect animal, do nothing
						cout << "Animal was not removed." << endl;
						return animals;
					}
					else {
						cout << "Please enter Y or N to confirm." << endl;
					}
				}
			} catch (int x) {
				cout << "There was an error when removing animal, please try again." << endl;
			}
		}
		else {												//If tracking num not found
			cout << "Tracking Number not found. Try again." << endl;
		}
	}
	return animals;
}

//saves current vector to file zoodata.txt
void SaveDataToFile(vector<zooAnimals> animals)
{
	ofstream outputFile;
	outputFile.open("zoodata.txt", ios::out);

     try {
    	 for (unsigned int i = 0; i < animals.size(); ++i) {		//for each animal in vector, convert data to char's and then save to file
    		 //char trackingNum = '0';
    		 //itoa(animals.at(i).trackingNum, )
    		 int nameLength = animals.at(i).name.length();
    		 char nameArray[nameLength + 1];
    		 int typeLength = animals.at(i).type.length();
    		 char typeArray[typeLength + 1];
    		 int subTypeLength = animals.at(i).subType.length();
    		 char subTypeArray[subTypeLength + 1];
    		 char numEggs = '0' + animals.at(i).numEggs;
    		 char nursing = '0' + animals.at(i).nursing;
    		 strcpy(nameArray, animals.at(i).name.c_str());
    		 strcpy(typeArray, animals.at(i).type.c_str());
    		 strcpy(subTypeArray, animals.at(i).subType.c_str());

    		 outputFile << setw(6) << setfill('0') << animals.at(i).trackingNum << setw(15) << setfill(' ') << nameArray << setw(15) << setfill(' ') << typeArray << setw(15) << setfill(' ') << subTypeArray;
    		 outputFile << "     " << numEggs;
    		 outputFile << "     " << nursing << endl;
    	 }
    	 cout << "Data successfully saved to zoodata.txt." << endl;
    	 outputFile.close();		//never forget to close a file!
     } catch (int x) {
    	 cout << "Failed to save data to txt file." << endl;
     }
}

//Displays the menu
void DisplayMenu()
{
     cout << "Menu: " << endl;
     cout << "1. Load Animal Data" << endl;
     cout << "2. Generate Data" << endl;
     cout << "3. Display Animal Data" << endl;
     cout << "4. Add Record" << endl;
     cout << "5. Delete Record" << endl;
     cout << "6. Save Animal Data" << endl;
     cout << "7. End program" << endl;
     cout << "Enter choice: ";
}



int main()
{
	//start the vector
	vector<zooAnimals> animals;
	int choice = 0; 		//user menu item choice
	while(choice != 7) {
		DisplayMenu();
		cin >> choice;
		switch(choice){
		case 1: {										//load data from file
			animals = LoadDataFromFile();
			break;
		}
		case 2: {										//Generate data using the .java file
			GenerateData();
			animals = LoadDataFromFile();
			break;
		}
		case 3: {										//Display all the animals in the vector in a table
			cout << setw(15) << setfill(' ') << left << "Track #|";
			cout << setw(15) << setfill(' ') << left << "Name ";
			cout << setw(15) << setfill(' ') << left << " Type ";
			cout << setw(15) << setfill(' ') << left << " Sub-Type ";
			cout << setw(15) << setfill(' ') << left << " Eggs ";
			cout << setw(15) << setfill(' ') << left << " Nurse " << endl;
			for(unsigned int i = 0; i < animals.size(); ++i) {
				DisplayAnimal(animals.at(i));
			}
			break;
		}
		case 4: {										//add animal to end of vector
			animals.push_back(AddAnimal());
			break;
		}
		case 5: {										//remove animal from vector
			int trackingNum = 0;
			cout << "Enter tracking number: ";
			cin >> trackingNum;
			animals = RemoveAnimal(trackingNum, animals);
			break;
		}
		case 6: {										//save vector to zoodata.txt
			SaveDataToFile(animals);
			break;
		}
		}
	}
	return 1;
}
