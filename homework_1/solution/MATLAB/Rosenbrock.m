% 定义目标函数
f = @(x, y) 100*(x.^2 - y).^2 + (x - 1).^2;

% 定义网格范围
x = linspace(-2, 2, 100);
y = linspace(-1, 3, 100);

% 生成网格
[X, Y] = meshgrid(x, y);

% 计算函数值
Z = f(X, Y);

% 绘制函数图像
mesh(X, Y, Z);
xlabel('x');
ylabel('y');
zlabel('f(x, y)');
title('Rosenbrock Function');
