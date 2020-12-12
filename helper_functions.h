int mosfet=1;
int wires=1;
vector<string> AND_out;
vector<string> PDN;
string longchain;
vector<string> OutPut;
int outputWire;
vector<int> indcies;



bool is_valid(string exp){
	//wrong input
	if (exp.size() <= 1)
		return false;
	//First we check the first and the last characters
	if(exp[0]=='|' || exp[0]=='&' ||exp[0] =='\'' || exp[exp.size() - 1] == '|' || exp[exp.size() - 1] == '&')
		return false;
	string temp="";
	//Second we check the string is only lowercase or upper case and if not we transform it to lowercase
	for (char x: exp)
		temp+=char (tolower(x));
	for (int i = 0; i < temp.size() - 1; i++)
	{	if(temp[i]==temp[i+1])
		{return false;break;}
		if (temp[i] == '\'')
		{
			if (i == 0 || temp[i - 1] == '|' || temp[i - 1] == '&' || temp[i - 1] == '\'' )
				return false;
			else if (temp[i + 1] != '|' && temp[i + 1] != '&' &&temp[i + 1] != ')')
				return false;
		}
		
		else if (temp[i] == '|' || temp[i] == '&' )
		{
			if (temp[i + 1] == '|' || temp[i + 1] == '&' || temp[i + 1] == '\'')
				{return false;}
		}
		
		else if (int(temp[i]) >= 97 && int(temp[i]) <= 122  )
		{	
			
				// checking that there after each character ther is only the allowed character
			if (int(temp[i + 1]) != '|' && int(temp[i + 1]) != '&' &&int(temp[i + 1]) != '\'' )
				return false;
				//Then checking that there are no consecutive characters 
			else if (int(temp[i + 1]) >= 97 && int(temp[i + 1]) <= 122)
				return false;

			

		}

	
	
}return true;
	}
//This function parses the input using the semicolons
unordered_map <string,string> semicolon(const string&  exp) {
   unordered_map <string,string> exps;
   vector<string> keys;
   string key;
   stringstream st(exp); 
   while (st.good()) {
	   string expression; string output;
   		getline(st, output, '=');
   		getline(st,expression,';');
   		exps[output]=expression;
   		//keys.push_back(key);
   }
   return exps;
}
//This function get the expressions in a vector from the map 
vector<string> get_exps(unordered_map <string,string> exps){
	vector<string> ex;
	unordered_map <string,string>::iterator it;
	
	for(it =exps.begin(); it!=exps.end(); it++)
	{ex.push_back(it->second);}
	return ex;
	}

vector<string> get_out(unordered_map <string,string> exps){
	vector<string> ex;
	unordered_map <string,string>::iterator it;
	
	for(it =exps.begin(); it!=exps.end(); it++)
	{ex.push_back(it->first);}
	return ex;
	}
void AND(string first, string second,int& U, int& D,int lines)
{
  string out=first;
    if(U==-1)
    {
        cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<first<<"\tVDD\tVDD\tPMOS"<<endl;
        out= "W"+to_string(wires);
        mosfet++;
        longchain=to_string(wires);
        wires++;
        //AND_out.push_back("W"+);
    }
   
    cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<second<<"\tW"<<longchain<<"\tW"<<longchain<<"\tPMOS"<<endl;
    out="W"+to_string(wires);
    mosfet++;
    longchain=to_string(wires);
    wires++;
   OutPut[lines]=("W"+to_string(wires-1));
    //---------------------PDN----------------------------//
  if(D==-1)   {if(U==-1)
    {cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)      <<"\t"<<first<<"\t0\t0\tNMOS"<<endl;
      mosfet++;
      AND_out.push_back("W"+to_string(wires));
        wires++;
      U++;
    }
    cout<<"M"+to_string(mosfet)<<"\t"<<AND_out[AND_out.size()-1]<<"\t"<<second<<"\t0\t0\tNMOS"<<endl;
     mosfet++;
      PDN.push_back(AND_out[D+1]);
      
  }
    else
    {
        if(U==-1)
          {cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)      <<"\t"<<first<<"\t"<<AND_out[D]<<"\t"<<AND_out[D]<<"\tNMOS"<<endl;
            mosfet++;
            AND_out.push_back("W"+to_string(wires)); wires++;
            U++;
          }
        cout<<"M"+to_string(mosfet)<<"\t"<<AND_out[AND_out.size()-1]<<"\t"<<second<<"\t"<<AND_out[D]<<"\t"<<AND_out[D]<<"\tNMOS"<<endl;
        D++;
    }
}
string Not (string inverse)
{
    cout<<"Inversion of "<<inverse<<endl;
    cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<inverse<<"\tvdd\tvdd"<<"\tPMOS"<<endl;
    mosfet++;
    cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<inverse<<"\t0\t0"<<"\tNMOS"<<endl;
    wires++;
    cout<<endl;
    return ("W"+to_string(wires-1));
}
void OR(string value, int position)
{
    cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<value<<"\tVDD\tVDD\tPMOS"<<endl;
    mosfet++;
    OutPut[position]=("W"+to_string(wires));
    wires++;
    if(AND_out.size()>0)
    {
    cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<value<<"\t"<<AND_out[AND_out.size()-1]<<"\t"<<AND_out[AND_out.size()-1]<<"\tNMOS"<<endl;
    AND_out.push_back("W"+to_string(wires));  mosfet++; wires++;
    }
    else
    {
        cout<<"M"+to_string(mosfet)<<"\tW"+to_string(wires)<<"\t"<<value<<"\t0\t0\tNMOS"<<endl;
        AND_out.push_back("W"+to_string(wires));  mosfet++; wires++;
    }
}
void generateFunction (string y, string out)
{
    int lines=1;
  int x=-1;
    int d=-1;string And;
  int mult=0;
  int flag=1;
  int numberOfAndGates=-1;
    int gates=1;
    bool called=0;
    for(int i=0;i<y.length();i++)
    {
      if(y[i]=='&')
      {
        flag++;
      }
      else if(y[i]=='|')
      {
          gates++;
        flag=1;
        mult=1;
      }
        if(outputWire<=flag)
        {
          outputWire=flag;
        }
    }
   //cout<<gates<<"\t"<<mult<<endl;
      OutPut.resize(gates+1);
    for(int i=0;i<y.length();i++)
    {
      if((y[i]=='&')&&(x==-1))
      {string f="";
          if(y[i-1]=='\'')
          { f=f+y[i-2];}
        else
        {
            f=Not(f=f+y[i-1]);
        }
        string s="";
          if(y[i+2]=='\'')
       { s=s+y[i+1];}
        else
        {
            s=Not(s=s+y[i+1]);
        }
          called=1;
          AND (f,s,x,d,lines);
       numberOfAndGates++;
      }
      else if((y[i]=='&')&&(x>-1))
      {
         string f="";
          if(y[i+2]=='\'')
          {
              f=f+y[i+1];
          }
          else
          {
              f=Not(f=f+y[i+1]);
          }
          called=1;
        AND (AND_out[numberOfAndGates],f,x,d,lines);
         numberOfAndGates++;
      }
      if(y[i]=='|')
      {
          x=-1; numberOfAndGates=-1;
          lines++;
          if(called==1)
          {d++;}
          //if(x!=-1){d++;}
      }
    }
      string z="";  int flag2=0;   string substring="";
      y=y+'|';
      int ind=1;
      for(int i=0;i<y.length();i++)
      {
          substring=substring+y[i];
          if(y[i]=='&')
          {
             
              flag2=1;
          }
          if(y[i]=='|')
          {
              
              if(flag2==0)
              {
                  indcies.push_back(ind);
                  z=z+substring;
                  
              }
              substring.clear();
              flag2=0;
              ind++;
          }

      }
      //cout<<z<<endl;
      int pos=0;
      for(int i=0;i<z.length();i++)
      {
          if(z[i]=='|')
          {
              string v="";
              if(z[i-1]=='\'')
              {
                  v=v+z[i-2];
                  OR(v,indcies[pos]);
                  pos++;
              }
              else
              {
                  v=Not(v=v+z[i-1]);
                  OR(v,indcies[pos]);
                  pos++;
              }
          }
      }
      OutPut[0]=("W"+to_string(wires-1));
      cout<<"the output "+out;
      for(int i=0;i<OutPut.size();i++)
      {
          if(OutPut[i]!="")
        {  cout<<"="<<OutPut[i];}
      }
    cout<<endl;
}
