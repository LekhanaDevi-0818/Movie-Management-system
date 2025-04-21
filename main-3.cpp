#include<iostream>
using namespace std;

// Movies node
class Movie{
    public:
        string m_name;  // name of the movie
        string m_date;   // date of the mvovie
        Movie* left;  // pointer (previous movie)
        Movie* right; // pointer (next movie)

        Movie(string m_name,string m_date){
            this->m_name = m_name;
            this->m_date = m_date;
            this->left = nullptr; //null pointer
            this->right = nullptr; //null pointer 
        }
};
class movie_Category{// category class consists of movie list.
    public: 
        string Moviename;
        Movie* ML_Head;  // movie list head in a category
        Movie* ML_Tail;  // movie list tail in a category
        movie_Category* prev;       /// pointer - prev category
        movie_Category* next;   // pointer - next category

        movie_Category(string name_mve){
            this->Moviename = name_mve;
            this->ML_Head = nullptr;
            this->ML_Tail = nullptr;
            this->next = nullptr; 
            this->prev = nullptr;
        }
        void adding_Movie(string name_mve,string date_mve){
            if(ML_Head == nullptr){  // 1st movie in list
                ML_Head = new Movie(name_mve,date_mve);
                ML_Tail = ML_Head;
                ML_Head->left = ML_Head; // CLL
                ML_Head->right = ML_Head;
                return;
            }
            else{
                Movie* temp = ML_Head; // insertion into sorted order
                while(temp!=ML_Tail && temp->m_name <= name_mve){
                    if(temp->m_name == name_mve){ //exists.
                        return;
                    }
                    temp = temp->right;
                }
                if(temp == ML_Tail){ // end of the list
                    if(temp->m_name ==name_mve) // exists
                    return; 
                    if(temp->m_name <= name_mve){
                        Movie* newMovie = new Movie(name_mve,date_mve);// insertion at the last 
                        temp->right = newMovie; 
                        newMovie->right=ML_Head;
                        newMovie->left = temp;
                        ML_Tail = newMovie; // updating the tail pointer with new node
                        return;
                    }
                }
            }
        }
        Movie* Middle(Movie* starting, Movie* ending) { 
            if (starting == NULL) //  computing the middle pointer using binary search
                return NULL; 
             Movie* S = starting; 
            Movie* F = starting -> right; 
            while (F != ending){ 
                F = F -> right; 
                 if (F != ending){ 
                    S = S -> right; 
                    F = F -> right; 
               } 
            } 
        return S; 
    } 
        Movie* Movie_binarySearch(string name){
            if(ML_Head==nullptr)return nullptr;
            Movie* first = ML_Head; // binary searching first pointer
            Movie* last = ML_Tail;  // binary searching last pointer
            while(first!=last){
                Movie* middle = Middle(first,last);// finding the middle pointer using binary search 
               if(middle->m_name == name)return middle; // movie found
               else if(middle->m_name > name){     // movie name < movie to be searched
                                                // reducing the range
                   last = middle->left;        // first,middle->left - range
               }
               else {
                   first= middle->right; // middle->right,last - range
               }
            }
            if(first->m_name!=name)
            return nullptr; // movie == not found
            else
            return first;   // movie == found
        }
        int Movie_Ind(string given_name){
             Movie*  temp = ML_Head;
             int idx = 0;
             while(temp!=ML_Tail && temp->m_name!=given_name){  
                 temp=temp->right;
                 idx = idx + 1;
             }
             if(temp->m_name != given_name)
             return -1; 
             return idx; 
        }
        void print_movies_categories(){
             Movie*  temp = ML_Head;
             
             while(temp!=ML_Tail){
                 cout << "Movie name:- "<<temp->m_name<<"; date: "<<temp->m_date; // printing the movie with dates
                 cout << endl; 
                 temp=temp->right;
             }
          
             cout<<"Movie name:- "<<temp->m_name<<"; date: "<<temp->m_date;
             cout << endl;
             return ;
        }
};
class M_Categories{
        public:
            movie_Category *head_prev; // pointer - head of list of category
            M_Categories(){
                head_prev = nullptr;
            }
            void adding_Category(string name){
                 movie_Category* category = new movie_Category(name);
                 if(head_prev == nullptr){  // 1st category
                     head_prev = category;
                     return;
                 }
                movie_Category *temp = head_prev;
                while(temp->next!=nullptr){
                    temp = temp->next;
                }
                temp->next = category;// inserting in the last
                category->prev = temp;
                category->next = nullptr;
            }
                void removing_Category(string name){ // removing category by name
                movie_Category* temp = head_prev;
               movie_Category* ctgry = searching_movieName(name); // searching pointer with given name
                if(ctgry==nullptr)
                return; 
                Movie* mve = ctgry->ML_Head; // removing all the movies
                while( mve!=ctgry->ML_Tail){
                    Movie* dt = mve->right;
                    free(mve); // deallocating a block of memory previously allocated 
                    mve = dt;
                }
                free(mve);
                if(ctgry == head_prev){
                    head_prev = nullptr;
                    free(ctgry);
                }
                else{
                    ctgry->prev->next = ctgry->next;
                    if(ctgry->next!=nullptr)
                    ctgry->next->prev=ctgry->prev;
                    free(ctgry);
                }
            }
            movie_Category* searching_movieName(string name){
                movie_Category* temp = head_prev;
                while(temp!=nullptr && temp->Moviename!=name){// iteratating over the same list untill given name is not found
                    temp=temp->next;
                }
                return temp; // not found = NULL
            }
            Movie* searching_movie(string name){ //searching movie by name
                movie_Category *temp = head_prev;// checking all categories
                while(temp!=nullptr){
                    Movie* mve = temp->Movie_binarySearch(name); // searching movie category list using binary search 
                    if(mve!=nullptr){ // found
                        return mve;
                    }
                   temp=temp->next; // moving to next ctrgy 
                }
                return nullptr;
            }
            void deleting_movies(string date){ // deleting movies before inserting date.
                movie_Category *ctgry1 = head_prev;
                if(ctgry1!=nullptr){
                    Movie* mve1 = ctgry1->ML_Head;
                    while(mve1!=ctgry1->ML_Tail){
                        Movie* dt = mve1->right;// checking the date of each movie
                        if(mve1->m_date < date){
                             if(mve1 == ctgry1->ML_Head){
                                 ctgry1->ML_Head = mve1->right;
                                 free(mve1);
                             }
                             else{
                                 mve1->left->right = mve1->right;
                                 mve1->right->left = mve1->left;
                                 free(mve1);
                             }
                        }
                        mve1 = dt;
                    }
                    if(mve1->m_date < date){
                        if(mve1==ctgry1->ML_Head){
                            ctgry1->ML_Head;
                            ctgry1->ML_Head = ctgry1-> ML_Tail;
                            ctgry1->ML_Tail = nullptr;
                            
                            free(mve1);
                        }
                    }
                }
                return;
            }
};


int main(){
    M_Categories* category = new M_Categories();
    category->adding_Category("Children:\n");
    category->adding_Category("Action:\n");
    category->adding_Category("Comedy:\n");
     movie_Category* category1 = category->head_prev;
    
   category->head_prev->adding_Movie("Barbie","10-21-2001");
   category->head_prev->adding_Movie("Harry Potter","11-14-2001");
   category->head_prev->adding_Movie("Lion King","06-24-1994");
   category1 = category1->next;
   
   category1->adding_Movie("MI-5","05-08-2005");
   category1->adding_Movie("Rocky","11-27-1976");
   category1->adding_Movie("Taken","02-27-2008");
   category1 = category1->next;

   category1->adding_Movie("Harold & Kumar","07-30-2024");
   category1->adding_Movie("Jerry McGuire","12-13-1996");
   category1->adding_Movie("Tuxedo","09-27-2002\n");

   category1=category->head_prev;
   while(category1!=nullptr){
       cout<<category1->Moviename;
       category1->print_movies_categories();
       category1 = category1->next;
   }
   Movie* movie = category->searching_movie("Barbie");
   if(movie!=nullptr){
       cout<<"Barbie is in the list";
       cout<< endl;
   }
   else 
   cout <<"Barbie is not in the list";
   cout << endl;
   
   category->removing_Category("children"); // removing children category
   movie = category->searching_movie("Barbie"); // searching for a movie from children category after removing children category
   if(movie!=nullptr){
       cout<<"After removing children category Barbie is not in the list";
   }
   else
   cout<<"After removing children category Barbie is in the list";
}
