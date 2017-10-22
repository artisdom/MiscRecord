library(ggplot2)
library(showtext)
showtext.auto(enable = TRUE)
font.add('Broman', 'SimHei.ttf')
pdf('test2.pdf')
ggplot(data.frame(x = rnorm(100))) +
    geom_histogram(aes(x), fill = 'purple', alpha = 0.6) +
    labs(x = 'X ȡֵ', y = 'Ƶ�� Count', title = '���� Title') +
    theme(text = element_text(family = 'Broman'))
dev.off()