package zad1;

import java.io.File;
import com.fasterxml.jackson.databind.ObjectMapper;

public class BookParser {

	public static void main(String[] args) throws Exception, Exception {
		
		ObjectMapper mapper = new ObjectMapper();
		
		Data data = mapper.readValue(new File("src/files/Bookstore.json"), Data.class);
		
		for(Books books: data.getBooks()) {
			System.out.println(books.getRemark());
		}

	}

}
