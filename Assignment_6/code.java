import java.util.Scanner;

public class code {

    public static void dijkstra_algo(int[][] arr, int[] cost, int[] prev, int source, int nodes) {
        int visited[] = new int[nodes + 1];

        for (int i = 1; i <= nodes; i++) {
            cost[i] = prev[i] = visited[i] = -1;
        }

        cost[source] = 0;
        prev[source] = source;

        while (true) {
            int nodeIndex = -1;
            int temp = Integer.MAX_VALUE;

            for (int i = 1; i <= nodes; i++) {
                if (visited[i] == -1 && cost[i] != -1 && cost[i] < temp) {
                    temp = cost[i];
                    nodeIndex = i;
                }
            }

            if (nodeIndex == -1) {
                break;
            }

            visited[nodeIndex] = 1;

            for (int j = 1; j <= nodes; j++) {
                if (visited[j] == -1 && arr[nodeIndex][j] != -1
                        && (arr[nodeIndex][j] + cost[nodeIndex] < cost[j] || cost[j] == -1)) {
                    cost[j] = arr[nodeIndex][j] + cost[nodeIndex];
                    prev[j] = nodeIndex;
                }
            }
        }
    }

    public static int next_node(int[] prev, int j, int source) {
        if (prev[j] == source)
            return j;

        return next_node(prev, prev[j], source);
    }

    public static void main(String[] args) {
        Scanner read = new Scanner(System.in);

        System.out.print("Enter the number of routers : ");

        int nodes = read.nextInt();

        System.out.print("Enter the number of links : ");

        int edges = read.nextInt();

        int arr[][] = new int[nodes + 1][nodes + 1];

        for (int i = 0; i <= nodes; i++) {
            for (int j = 0; j <= nodes; j++) {
                arr[i][j] = -1;

                if (i == j) {
                    arr[i][j] = 0;
                }
            }
        }

        System.out.println("Enter the router pair and the cost : ");

        for (int i = 0; i < edges; i++) {
            int x, y, w;
            x = read.nextInt();
            y = read.nextInt();
            w = read.nextInt();

            arr[x][y] = w;
            arr[y][x] = w;
        }

        System.out.println("\n\nNetwork : \n");

        System.out.print("    ");
        for (int i = 1; i <= nodes; i++) {
            System.out.print(i + " ");
        }

        System.out.println("\n");

        for (int i = 1; i <= nodes; i++) {
            System.out.print(i + "   ");
            for (int j = 1; j <= nodes; j++) {
                if (arr[i][j] == -1) {
                    System.out.print("- ");
                }

                else {
                    System.out.print(arr[i][j] + " ");
                }
            }
            System.out.print("\n");
        }

        int cost[] = new int[nodes + 1];
        int prev[] = new int[nodes + 1];

        for (int i = 1; i <= nodes; i++) {

            System.out.println("-----------------------------------------");
            System.out.println("\nFinal Routing table for router " + i + " : \n");

            dijkstra_algo(arr, cost, prev, i, nodes);

            for (int j = 1; j <= nodes; j++) {

                int next = next_node(prev, j, i);

                System.out.print(i + " -> " + j + " : " + cost[j] + " ");

                if (next == j) {
                    System.out.println("-");
                } else {
                    System.out.println(next);
                }
            }
        }
    }
}
