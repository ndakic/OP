package zad1;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Magazines {

	  private String title; 
	  private String month; 
	  private int year; 

	  public String getTitle(){
	  	return title; 
	  }
	  @JsonProperty("Title")
	  public void setTitle(String input){
	  	 this.title = input;
	  }
	  public String getMonth(){
	  	return month; 
	  }
	  @JsonProperty("Month")
	  public void setMonth(String input){
	  	 this.month = input;
	  }
	  public int getYear(){
	  	return year; 
	  }
	  @JsonProperty("Year")
	  public void setYear(int input){
	  	 this.year = input;
	  }
	@Override
	public String toString() {
		return "Magazines [title=" + title + ", month=" + month + ", year=" + year + "]";
	}
	  
	  
	
}
