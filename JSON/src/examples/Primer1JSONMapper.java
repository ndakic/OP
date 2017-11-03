package examples;

import java.io.File;
import java.io.IOException;
import java.util.Map;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Primer1JSONMapper {

	public static void main(String[] args) throws Exception, JsonMappingException, Exception {
		
		ObjectMapper mapper = new ObjectMapper();
		
		Book book = mapper.readValue(new File("src/files/Book.json"), Book.class);
		
		System.out.println(book.toString());
		
		
		book.setTitle("Changed book title");
		
		mapper.writeValue(new File("src/files/Book_changed.json"), book);
		
		// ==================================================================================
		
		
		Map<String, Object> b = mapper.readValue(new File("src/files/Book.json"), Map.class);
		
		b.put("newAttribute", "newValue");
		
		System.out.println(b.toString());

	}

}
