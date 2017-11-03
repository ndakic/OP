package zad1;

import java.util.List;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Books {
	
	  private String iSBN; 
	  private int price; 
	  private int edition; 
	  private String remark;
	  private String title; 
	  private List<Authors> authors; 

	  public String getISBN(){
	  	return iSBN; 
	  }
	  @JsonProperty("ISBN")
	  public void setISBN(String input){
	  	 this.iSBN = input;
	  }
	  public int getPrice(){
	  	return price; 
	  }
	  @JsonProperty("Price")
	  public void setPrice(int input){
	  	 this.price = input;
	  }
	  public int getEdition(){
	  	return edition; 
	  }
	  @JsonProperty("Edition")
	  public void setEdition(int input){
	  	 this.edition = input;
	  }
	  public String getTitle(){
	  	return title; 
	  }
	  @JsonProperty("Title")
	  public void setTitle(String input){
	  	 this.title = input;
	  }
	  public List<Authors> getAuthors(){
	  	return authors; 
	  }
	  @JsonProperty("Authors")
	  public void setAuthors(List<Authors> input){
	  	 this.authors = input;
	  }

	public String getRemark() {
		return remark;
	}
	 @JsonProperty("Remark")
	public void setRemark(String remark) {
		this.remark = remark;
	}
	@Override
	public String toString() {
		return "Books [iSBN=" + iSBN + ", price=" + price + ", edition=" + edition + ", remark=" + remark + ", title="
				+ title + ", authors=" + authors + "]";
	}
	 
	 
		  
	  

}
