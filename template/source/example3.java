import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

public class Main {
	static final int MAXN = 21;
	static final int MAXM = 110;
	static final int oo = 214000000;
	
	public static int read(Scanner cin) {
		char x = cin.next().charAt(0);
/*		while(x < 'A' || x > 'Z')
			x = cin.next().charAt(0);*/
		return x - 'L' + 1;
	}
	
	private static boolean contain(int s, int i) {
		return ((s >> i) & 1) == 1;
	}
	
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		try {
			cin = new Scanner(new FileInputStream("exclusive.in"));
		}catch(FileNotFoundException e) {
			System.exit(0);
		}
		PrintWriter out = new PrintWriter(System.out);
		try {
			out = new PrintWriter("exclusive.out", "UTF-8");
		}catch(FileNotFoundException e) {
			System.exit(0);
		}catch(UnsupportedEncodingException e) {
			System.exit(0);
		}
		
		int m, n = 15;
		m = cin.nextInt();
		int ea[] = new int [MAXM], eb[] = new int [MAXM];
		boolean hs[][] = new boolean [MAXN][MAXN];

		
		out.printf("%d\n", f[MAXS - 1] - 2);
		for(int i = 1; i <= m; ++i) {
			if(bel[ea[i]] < bel[eb[i]])
				out.printf("%c %c\n", ea[i] + 'K', eb[i] + 'K');
			else
				out.printf("%c %c\n", eb[i] + 'K', ea[i] + 'K');
		}
		out.close();
	}
}
