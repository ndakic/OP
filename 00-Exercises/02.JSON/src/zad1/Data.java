package zad1;

import java.util.List;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Data {

	  private List<Books> books; 
	  private List<Magazines> magazines; 
	
	  public List<Books> getBooks(){
	  	return books; 
	  }
	  @JsonProperty("Books")
	  public void setBooks(List<Books> input){
	  	 this.books = input;
	  }
	  public List<Magazines> getMagazines(){
	  	return magazines; 
	  }
	  @JsonProperty("Magazines")
	  public void setMagazines(List<Magazines> input){
	  	 this.magazines = input;
	  }
	@Override
	public String toString() {
		return "Data [books=" + books + ", magazines=" + magazines + "]";
	}
	  
	  
	
}
