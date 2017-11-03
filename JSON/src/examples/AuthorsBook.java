package examples;

import com.fasterxml.jackson.annotation.JsonAutoDetect;
import com.fasterxml.jackson.annotation.JsonAutoDetect.Visibility;

@JsonAutoDetect(fieldVisibility = Visibility.ANY)
public class AuthorsBook {
	
	private String firstName;
	private String lastName;
	private String bookTitle;
	
	
	public String getFirstName() {
		return firstName;
	}
	public void setFirstName(String firstaName) {
		this.firstName = firstaName;
	}
	public String getLastName() {
		return lastName;
	}
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	public String getBookTitle() {
		return bookTitle;
	}
	public void setBookTitle(String bookTitle) {
		this.bookTitle = bookTitle;
	}
	@Override
	public String toString() {
		return "AuthorsBook [firstName=" + firstName + ", lastName=" + lastName + ", bookTitle=" + bookTitle + "]";
	}
	
	

}
