package zad1;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Authors {

	  private String firstName; 
	  private String lastName; 

	  public String getFirstName(){
	  	return firstName; 
	  }
	  @JsonProperty("First_Name")
	  public void setFirstName(String input){
	  	 this.firstName = input;
	  }
	  public String getLastName(){
	  	return lastName; 
	  }
	  @JsonProperty("Last_Name")
	  public void setLastName(String input){
	  	 this.lastName = input;
	  }
	@Override
	public String toString() {
		return "Authors [firstName=" + firstName + ", lastName=" + lastName + "]";
	}
	  
	  
	
}
