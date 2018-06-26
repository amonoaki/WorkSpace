package userinterface;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import actioninterface.*;

public class Layout
{
	private JFrame jFrame = new JFrame();
	private JTabbedPane jTabbedPane = new JTabbedPane();
    private JMenuBar jMenuBar = new JMenuBar();
    private JMenu file = new JMenu("File");
    //private ProcessFile processFile = new ProcessFile();
    
    private int new_file_count = 0;
    private JMenuItem openFile, newFile, saveFile;
    private JTextArea page;

    public int getNewFileCount() {
    	return new_file_count;
    }
    public JMenuItem getOpenFile() {
    	return openFile;
    }
    public JMenuItem getNewFile() {
    	return newFile;
    }
    public JMenuItem getSaveFile() {
    	return saveFile;
    }
    public JTextArea getTextAreaPage() {
    	return page;
    }

    public void init() {
    	
    	jFrame.setTitle("MyEditor");  //设置标题
        jFrame.setBounds(200, 100, 1000, 800);  //设置边界及窗口位置
        jFrame.setLayout(new GridLayout(1, 1));
    	
        /*菜单栏*/
        //子菜单
        openFile = new JMenuItem("Open File");
        openFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));  //子菜单和快捷键CTRL-O绑定
        openFile.addActionListener(new ProcessFile());  //子菜单注册ProcessFile监视器，下同
        
        newFile = new JMenuItem("New File");
        newFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, ActionEvent.CTRL_MASK));  //子菜单和快捷键CTRL-N绑定
        newFile.addActionListener(new ProcessFile());
        
        saveFile = new JMenuItem("Save File");
        saveFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, ActionEvent.CTRL_MASK));  //子菜单和快捷键CTRL-S绑定
        saveFile.addActionListener(new ProcessFile());
        
        //菜单项
        file.add(openFile);
        file.add(newFile);
        file.add(saveFile);
        //菜单项加到菜单栏中
        jMenuBar.add(file);
        //将菜单栏添加到窗口
        jFrame.setJMenuBar(jMenuBar);

        /*主面板*/
        jFrame.add(jTabbedPane);
        createTab("Welcome Page", "This is the welcome page.");
        
        jFrame.setVisible(true);  //使窗口可见
        jFrame.setDefaultCloseOperation(jFrame.DISPOSE_ON_CLOSE);  //点击关闭按钮销毁窗口
    }
    
    public void createTab(String tabName, String str){  //str为页面的内容
        page = new JTextArea(str);
        jTabbedPane.add(tabName, page);
        new_file_count++;
    }
}