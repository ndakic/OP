package zadaci;

import java.util.Date;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonProperty;


public class Log {
	
	private String Time;
	private String Date;
	private String User;
	private String Warning;
	private String Fatal;
	private List <Stack> Stack;
	
	public Log() {
		super();
	}



	public Log(String time, String date, String user, String warning, String fatal, List<zadaci.Stack> stack) {
		super();
		Time = time;
		Date = date;
		User = user;
		Warning = warning;
		Fatal = fatal;
		Stack = stack;
	}



	public String getTime() {
		return Time;
	}
	@JsonProperty("Time")
	public void setTime(String time) {
		Time = time;
	}

	public String getDate() {
		return Date;
	}
	@JsonProperty("Date")
	public void setDate(String date) {
		Date = date;
	}

	public String getUser() {
		return User;
	}
	@JsonProperty("User")
	public void setUser(String user) {
		User = user;
	}

	public String getWarning() {
		return Warning;
	}
	@JsonProperty("Warning")
	public void setWarning(String warning) {
		Warning = warning;
	}

	public String getFatal() {
		return Fatal;
	}
	@JsonProperty("Fatal")
	public void setFatal(String fatal) {
		Fatal = fatal;
	}


	public List<Stack> getStack() {
		return Stack;
	}


	@JsonProperty("Stack")
	public void setStack(List<Stack> stack) {
		Stack = stack;
	}



	@Override
	public String toString() {
		return "Log [Time=" + Time + ", Date=" + Date + ", User=" + User + ", Warning=" + Warning + ", Fatal=" + Fatal
				+ ", Stack=" + Stack + "]";
	}

	
	
}


