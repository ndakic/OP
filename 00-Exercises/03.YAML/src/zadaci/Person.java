package zadaci;

public class Person {
	
	private String name;
	private String surname;
	private int age;
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSurname() {
		return surname;
	}
	public void setSurname(String surname) {
		this.surname = surname;
	}
	public int getAgel() {
		return age;
	}
	public void setAgel(int agel) {
		this.age = agel;
	}
	@Override
	public String toString() {
		return "Person [name=" + name + ", surname=" + surname + ", age=" + age + "]";
	}
	
	

}


