
#include <vector>
using namespace std;

//struct RGB
//{
//int R;
//int G;
//int B;
//};

class FocusingClass
{
	private:
		int NextFocus;
	public:
	int currentFocusPosition;

	typedef struct focusingInfo
	{
		double dispersion;
		int focusPosition;
	};

	vector <FocusingClass::focusingInfo*> finfos;



	FocusingClass()
	{
		currentFocusPosition=0;
		NextFocus=5;
		stop=false;
	}

	/*
	void NextIter(RGB**inc_arr,int x_dim,int y_dim)
	{
		//Luminance=0.3*R+0.59*G+0.11*B
		double ** Luminance=new double*[y_dim];
		for(int i=0;i<y_dim;i++)
		{
			Luminance[i]=new double[x_dim];
			for(int j=0;j<x_dim;j++)
			{
				Luminance[i][j]=inc_arr[i][j].R*0.3+0.59*inc_arr[i][j].G+0.11*inc_arr[i][j].B;
			}
		}
		focusingInfo*finf=new focusingInfo;

		double Disp=Dispersion(Luminance,x_dim,y_dim);
		finf->dispersion=Disp;
		finf->focusPosition=currentFocusPosition;

		finfos.push_back(finf);
	}*/
	bool stop;
	double dabs(double i)
	{
		return i>0?i:-1*i;
	}
	void NextIter(double **Luminance,int x_dim,int y_dim)
	{
		focusingInfo*finf=new focusingInfo;
		double Disp=Dispersion(Luminance,x_dim,y_dim);
		finf->dispersion=Disp;
		finf->focusPosition=currentFocusPosition;
		finfos.push_back(finf);

		if(finfos.size()>1 && stop==false)
		{		
			int last_index=(int)finfos.size()-1;	
			if(finfos.size()>50)
			{
				if(dabs((finfos[last_index]->dispersion - finfos[last_index-8]->dispersion)/finfos[last_index]->dispersion)<0.001)
					stop=true;
			}


			
			if(finfos[last_index]->dispersion > finfos[last_index-1]->dispersion || dabs((finfos[last_index]->dispersion - finfos[last_index-1]->dispersion)/finfos[last_index]->dispersion)<0.001)
			{
				NextFocus=finfos[last_index-1]->focusPosition;		 
			}
			else
			{
				NextFocus=finfos[last_index-1]->focusPosition*-1;
			}


		}
		if(stop)
			NextFocus=0;
	}

	int getNextFocus()
	{
		currentFocusPosition=NextFocus;
		return NextFocus;
	}

	double Dispersion(double**lum_array,int x_dim,int y_dim)
	{
		return M1(lum_array,x_dim,y_dim);
	}

	double M1(double**lum_array,int x_dim,int y_dim)
	{
		double m_=M(lum_array,x_dim,y_dim);
		double ret=0;

		for(int i=0;i<x_dim;i++)
		{
			for(int j=0;j<y_dim;j++)
			{
				ret+=(lum_array[i][j]-m_)*(lum_array[i][j]-m_);
			}
		}

		return ret/(x_dim*y_dim);
	}

	double M(double**lum_array,int x_dim,int y_dim)
	{
		double ret=0;

		for(int i=0;i<x_dim;i++)
		{
			for(int j=0;j<y_dim;j++)
			{
				ret+=lum_array[i][j];
			}
		}

		return ret/(x_dim*y_dim);
	}
};