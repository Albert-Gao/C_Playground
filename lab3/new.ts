8 pages

1. find
interface IFindService{
	List<IRestaurant> findByKeyword(keyword:String)
	string convertVoiceToString() //?
}

2. History
//It suppose to have the ablities to retrieve and store information in the localStorage.

interface IStorageService{
	int save(key:string){},
	int get(key:string){},
	int delete(key:string){},
	int update(key:string){}
}

interface IRestaurant{
	title:string,
	iconURL:string,
	category:string,
	phone:string,
	address:string,
	location:double[,],
	ranking:number,
	favourite:boolean,
	saved:boolean
}

//Key List for the LocalStorage
historyList;
RecommendList;
FavList;
singRestaurant use its name as key;

3. Recommend
interface IRecommendService{
	List<IRestaurant> get();
}

4. Detail Page
interface detail{
    boolean addFav(title:string);
	IRestaurant get(title:string);
}
