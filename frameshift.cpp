/* Author: Denice Veluz
Course: CSCI - 136
Instructor: Maryash
Assignment: Project 2D
Compares with Task B and goes through each character until it finds AUG
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <climits>
using namespace std;

string transcriptase(string strand);
string add(string r,ifstream & dictionary);
string translate(string z, ifstream & dictionary);
int hammingDist(string str1, string str2);
string compare(string RNA1, string RNA2);
string TaskD(string B, ifstream & dictionary);

int main()
{
    ifstream fin("frameshift_mutations.txt");
    if (fin.fail()) {
        cerr << "mutations cannot be read, opened, or does not exist.\n";
        exit(1);
    }

    ifstream file("codons.tsv");
    if (file.fail()) {
        cerr << "codons cannot be read, opened, or does not exist.\n";
        exit(1);
    }
    
    string dna, strand;
    while(getline(fin, dna) && getline(fin, strand))
    {
        
        string x = transcriptase(dna);
        string mutation = transcriptase(strand);
        //cout << strand << " // " << dna <<endl;
        //cout << mutation << " // " << x <<endl;
       
        string protein2 = add(x, file);
        string protein1 = TaskD(mutation, file);
        cout << protein2 << endl;
        cout << protein1 << endl;
        

       
    }

}


string add(string r,ifstream & dictionary)
{
    //cout << "add is : " << r<<endl;
    string translation;
    bool to_translate = false;
    for(int i = 0; i <= r.length(); i+=3) //For loop to read sets of 3 in the string
    {

        string protein = translate(r.substr(i,3),dictionary);
        //cout << r.substr(i,3)<<" // " <<protein << endl;
        if(protein == "Met")
        {
            to_translate = true;
            translation = "Met";
        }
        else if(protein == "Stop")
        {
            to_translate = false;
            return translation;
        }
        if(to_translate == true && protein != "Met" && !protein.empty())
        {
            translation = translation + '-' + protein; //Adds hyphen to protein
            //cout << translation;
        }
   
    }
    return translation;
}


string translate(string z, ifstream & dictionary)
{
    
    dictionary.seekg(0);
    string protein, codon,to_return;
    while(dictionary >> codon >> protein) //Reads from the dictionary from the codon to the protein
    {
        //cout <<z<<" // " <<codon<<endl; //<< " || " <<protein<<endl;
        if (z == codon) //If mRNA from Task A is the same as the codon
        {
            return (to_return = protein);
        }
    }
    return to_return;
}

string transcriptase(string strand) //Put into function
{       
    for (int i = 0; i < strand.length(); i++) //Reads through the array
    {
        if(strand[i] == 'A' || strand[i] == 'a') //Changes A to U
        {    
            strand[i] = 'U';
        }

        else if(strand[i] == 'T' || strand[i] == 't') //Changes T to A
        {
            strand[i] = 'A';
        }

        else if(strand[i] == 'C' || strand[i] == 'c') //Changes C to G
        {
            strand[i] = 'G';
        }

        else if(strand[i] == 'G' || strand[i] == 'g') //Changes G to C
        {
            strand[i] = 'C';
        }
    }
    return strand;
}

int hammingDist(string str1, string str2) 
{ 
    int count = 0; 
    for (int i = 0; i < str1.length(); i++) 
    { 
        if (str1[i] != str2[i]) 
            count++; 
    } 
    return count; 
} 

string compare(string RNA1, string RNA2)
{
    //cout << RNA1.length() << " " << RNA2.length() <<endl;
    if(RNA1 == RNA2 )
    {
        return "no";
    }

    else if (RNA1.length()!= RNA2.length())
    {
        return "yes";
    }

    else
    {
        for (int i = 0; i < RNA1.length(); i+=4)
        {
            if(RNA1.substr(i,3) != RNA2.substr(i,3))
            {
                return "yes";
            }
            
     
       }
    }
    return "";
}

string TaskD(string B, ifstream & dictionary)
{
    for(int i=0; i < B.length(); i++)
    {
        if(B.substr(i,3) == "AUG")
        {
            return add(B.substr(i), dictionary);
        }
    }
return "";
}