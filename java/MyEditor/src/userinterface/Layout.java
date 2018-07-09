package userinterface;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import mylistenner.ProcessFileListenner;
import mylistenner.TabButtonListenner;
import mylistenner.TabPanelListener;

public class Layout extends JFrame
{
	private static final long serialVersionUID = 1L;
	private static int new_file_count = 0;  //现有标签页的数量（关闭标签页则减少）
	private static int tab_number = 0;  //标签页序号（关闭标签页不会减少，关闭程序归零）
	private static JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP, JTabbedPane.SCROLL_TAB_LAYOUT);
    private static JMenuBar menuBar = new JMenuBar();
    private static JMenu file = new JMenu("File");

	private JButton tabButton;
    private JLabel tabLabel;
    
    private ProcessFileListenner processFileListenner;
    private TabButtonListenner tabButtonListenner;
    private TabPanelListener tabPanelListener;
    
    public Layout() throws HeadlessException {
		super();
    	processFileListenner = new ProcessFileListenner(this);
    	tabButtonListenner = new TabButtonListenner(this);
    	tabPanelListener = new TabPanelListener(this);
	}

    public int getNewFileCount() {
    	return new_file_count;
    }
    public int getTabNumber() {
    	return tab_number;
    }
    public JTabbedPane getTabbedPane() {
    	return tabbedPane;
    }

    public void init() {
    	JMenuItem openFile, newFile, saveFile;
    	
    	setTitle("MyEditor");  //设置标题
        setBounds(200, 100, 1000, 800);  //设置边界及窗口位置
        setLayout(new GridLayout(1, 1));
    	
        /*菜单栏*/
        //子菜单
        openFile = new JMenuItem("Open File");
        openFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));  //子菜单和快捷键CTRL-O绑定
        openFile.addActionListener(processFileListenner);  //子菜单注册processFileListenner监视器，下同
        
        newFile = new JMenuItem("New File");
        newFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, ActionEvent.CTRL_MASK));  //子菜单和快捷键CTRL-N绑定
        newFile.addActionListener(processFileListenner);
        
        saveFile = new JMenuItem("Save File");
        saveFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, ActionEvent.CTRL_MASK));  //子菜单和快捷键CTRL-S绑定
        saveFile.addActionListener(processFileListenner);
        
        //菜单项
        file.add(openFile);
        file.add(newFile);
        file.add(saveFile);
        //菜单项加到菜单栏中
        menuBar.add(file);
        //将菜单栏添加到窗口
        setJMenuBar(menuBar);

        /*主面板*/
        add(tabbedPane);
        createTab("Welcome Page", "This is the welcome page.");
        
        setVisible(true);  //使窗口可见
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);  //点击关闭按钮销毁窗口
    }
    
    public void createTab(String tabName, String Text){  //Text为页面的内容
    	
    	JPanel tabPane = new JPanel(new FlowLayout());
    	JPanel pagePane = new JPanel(new BorderLayout());
    	
    	JTextArea page = new JTextArea(Text);
    	
        tabButton = new JButton();
        tabButton.addActionListener(tabButtonListenner);
        tabButton.addMouseListener(tabPanelListener);
        tabButton.setToolTipText("close "+tabName);
        tabButton.setContentAreaFilled(false);  //填充透明化
        tabButton.setBorderPainted(false);  //取消边界显示
        tabButton.setPreferredSize(new Dimension(13, 13));
        
        tabLabel = new JLabel(tabName);  //标签显示标签页的标签头
        
        tabPane.addMouseListener(tabPanelListener);
        tabPane.add(tabLabel);
        tabPane.add(tabButton);
        tabPane.setToolTipText(tabName);
        
        pagePane.add(page, BorderLayout.CENTER);
        
        tabbedPane.addTab(tabName, null, pagePane, tabName);
        tabbedPane.setTabComponentAt(tabbedPane.indexOfTab(tabName), tabPane);
        setActiveTabNamed(tabName);
        
        new_file_count++;
        tab_number++;
    }
    
    public void deleteTabNamed(String tabName) {
		int index = tabbedPane.indexOfTab(tabName);  //按标签页名字找到对应的标签页索引
		tabbedPane.remove(index);  //移除这一标签页
		new_file_count--;
    }
    
    public void setActiveTabNamed(String tabName) {
		int index = tabbedPane.indexOfTab(tabName);  //按标签页名字找到对应的标签页索引
		tabbedPane.setSelectedIndex(index);
    }
    
    public Component getTextArea() {
    	JPanel pagePane = (JPanel)tabbedPane.getSelectedComponent();
    	BorderLayout borderLayout = (BorderLayout)pagePane.getLayout();
    	return borderLayout.getLayoutComponent(BorderLayout.CENTER);
    }
    public Component getTextArea(String tabName) {
		int index = tabbedPane.indexOfTab(tabName);  //按标签页名字找到对应的标签页索引
		JPanel pagePane = (JPanel)tabbedPane.getComponentAt(index);
    	BorderLayout borderLayout = (BorderLayout)pagePane.getLayout();
    	
    	return borderLayout.getLayoutComponent(BorderLayout.CENTER);    	
    }
    
	public Component getTabComponent() {
		int index = tabbedPane.getSelectedIndex();
		
		return tabbedPane.getTabComponentAt(index);
	}
}
