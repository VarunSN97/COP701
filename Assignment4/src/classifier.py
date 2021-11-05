import pandas as pd
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score
import warnings

warnings.filterwarnings("ignore")
data = pd.read_csv("lib/breast_cancer.csv")
data.iloc[:,2:32]=StandardScaler().fit_transform(data.iloc[:,2:32])
data = data.iloc[:,1:32]
data.iloc[:,0]=data.iloc[:,0].apply(lambda x:0 if x=='M' else 1)

X_train,X_test,y_train,y_test = train_test_split(data.iloc[:,1:].values,data.iloc[:,0].values,train_size=0.8,shuffle=True)
clf = MLPClassifier((2,2),activation='logistic',max_iter=250)
clf.fit(X_train,y_train)
pred  = clf.predict(X_test)

print("PYthon: ")
print("Accuracy - ",accuracy_score(y_test,pred))
